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

const int N = 3e5 + 10; 
int n, m;
struct T { ll x[N], s[N]; } a, b;

void wa() { puts("-1"), exit(0); }

int main() {
	n = io();
	for(int i = 1 ; i <= n ; ++ i) a.x[i] = io(), a.s[i] = a.s[i - 1] + a.x[i];
	m = io();
	for(int i = 1 ; i <= m ; ++ i) b.x[i] = io(), b.s[i] = b.s[i - 1] + b.x[i];
	int p = 0, q = 0; ll sp = 0, sq = 0;
	if(a.s[n] != b.s[m]) {
		wa();
	} else {
		p = 1, q = 1, sp = a.x[1], sq = b.x[1];
		int ans = 0;
		while(1) {
			if(p > n || q > m) wa();
			while(sp < sq) {
				if(p + 1 > n) wa();
				sp += a.x[++ p];
			}
			while(sp > sq) {
				if(q + 1 > m) wa();
				sq += b.x[++ q];
			}
			if(sp == sq) {
				sp = a.x[++ p], sq = b.x[++ q];
				++ ans;
				if(p == n + 1 && q == m + 1) io(ans), exit(0);
			}
		}
	}
}
