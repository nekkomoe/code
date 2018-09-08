#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

ll f[20][20], dig[20];

int nxt(int s, int i) {
	return s + (i != 0);
}

ll dfs(int pos, int s, int bd) {
	if(s > 3) {
		return 0;
	} else if(pos == 0) {
		return s <= 3;
	} else if(!bd && f[pos][s] != -1) {
		return f[pos][s];
	} else {
		int top = bd ? dig[pos] : 9;
		ll sum = 0;
		for(int i = 0 ; i <= top ; ++ i) {
			sum += dfs(pos - 1, nxt(s, i), bd && i == top);
		}
		if(!bd) f[pos][s] = sum;
		return sum;
	}
}

void sol() {
	ll l = !io, r = !io;
	int tot = 0; while(r) dig[++ tot] = r % 10, r /= 10;
	ll ans = dfs(tot, 0, 1);
	-- l;
	if(l) {
		tot = 0; while(l) dig[++ tot] = l % 10, l /= 10;
		ans -= dfs(tot, 0, 1);
	} else -- ans;
	io(ans);
}

int main() {
	memset(f, -1, sizeof f);
	int T = io();
	while(T --) sol();
}
