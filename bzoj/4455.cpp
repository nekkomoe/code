// luogu-judger-enable-o2
%:pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 18;
int lk[N][N], p[N], tot;
ll f[N][N];
vector<int> g[N];

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

void dfs(int u, int fa) {
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v == fa) continue;
		dfs(v, u);
	}
	for(int i = 1 ; i <= tot ; ++ i) {
		int x = p[i];
		f[u][x] = 1;
		for(int j = 0 ; j < g[u].size() ; ++ j) {
			int v = g[u][j];
			if(v == fa) continue;
			ll sum = 0;
			for(int k = 1 ; k <= tot ; ++ k) {
				int y = p[k];
				if(lk[x][y] == 0) continue;
				sum += f[v][y];
			}
			f[u][x] *= sum;
		}
	}
}

int main() {
	int n = io.xuint(), m = io.xuint();
	for(int i = 1 ; i <= m ; ++ i) {
		int u = io.xuint(), v = io.xuint();
		lk[u][v] = lk[v][u] = 1;
	}
	for(int i = 1 ; i < n ; ++ i) {
		int u = io.xuint(), v = io.xuint();
		g[u].push_back(v), g[v].push_back(u);
	}
	ll ans = 0;
	for(int s = 0 ; s < (1 << n) ; ++ s) {
		tot = 0;
		for(int i = 1 ; i <= n ; ++ i)
			if((s >> (i - 1)) & 1)
				p[++ tot] = i;
		dfs(1, 0);
		ll sum = 0;
		for(int i = 1 ; i <= tot ; ++ i)
			sum += f[1][p[i]];
		ans += sum * (((n - tot) & 1) ? -1 : 1);
	}
	printf("%lld\n", ans);
}
