#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50000 + 10, inf = 0x3f3f3f3f;
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
    int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
int n, a[N * 2];
vector<int> g[N * 2]; ll ans;
int head[N * 2], rest[N * 4], w[N * 4], to[N * 4], tot = 1;
void addsig(int u, int v, int w) {
	to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int w) { addsig(u, v, w), addsig(v, u, w); }

void reb(int u, int fa) {
	int lst = u;
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v != fa) {
			reb(v, u), ++ n;
			a[n] = a[u]; 
			add(n, v, 1);
			add(lst, n, 0);
			lst = n;
		}
	}
}

int mx, rt, size, sz[N * 2], ban[N * 4];

void getrt(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(!ban[i] && v != fa) {
			getrt(v, u);
			sz[u] += sz[v];
			int k = max(size - sz[v], sz[v]);
			if(k < mx) rt = i, mx = k;
		}
	}
}

struct T { int val, len; };
bool operator < (T a, T b) { return a.val > b.val; }
vector<T> x, y;

void dfs(int u, int fa, int len, int val, vector<T> &x) {
	x.push_back((T) { val, len });
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(!ban[i] && v != fa) {
			dfs(v, u, len + w[i], min(val, a[v]), x);
		}
	}
}

void sol(int u, int size) {
	
	:: size = size, mx = inf, getrt(u, 0);
	
	if(mx == inf) return ;
	int rt = :: rt; ban[rt] = ban[rt ^ 1] = 1;
	
	x.clear(), y.clear();
	dfs(to[rt], 0, 0, a[to[rt]], x);
	dfs(to[rt ^ 1], 0, 0, a[to[rt ^ 1]], y);
	
	sort(x.begin(), x.end()), sort(y.begin(), y.end());
	
	for(int o = 1 ; o <= 2 ; ++ o) {
		for(int i = 0, j = 0, mx = -1 ; i < x.size() ; ++ i) {
			while(j < y.size() && y[j].val >= x[i].val) mx = max(mx, y[j].len), ++ j;
			if(~ mx) {
				ans = max(ans,
					(1ll + mx + x[i].len + w[rt]) * x[i].val);
			}
		}
		swap(x, y);
	}
	
	int tmp = sz[to[rt]];
	sol(to[rt], tmp), sol(to[rt ^ 1], size - tmp);
}

int main() {
	memset(a, 0x3f, sizeof a);
	n = io();
	for(int i = 1 ; i <= n ; ++ i) a[i] = io();
	for(int i = 1, u, v ; i < n ; ++ i)
		u = io(), v = io(),
		g[u].push_back(v), g[v].push_back(u);
	reb(1, 0);
	sol(1, n);
	printf("%lld\n", ans);
}
