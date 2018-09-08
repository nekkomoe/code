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
const int N = 1e5 + 10;
ll sa[N], sb[N], t[N], w, a[N], b[N], ans;
inline ll calc(int i, int j) {
	return min(sa[i], sb[j]) - (i + j) * w;
}
int main() {
//	freopen("data.in", "r", stdin);
	int n = io(); w = io();
	
	for(int i = 1 ; i <= n ; ++ i) a[i] = io();
	reverse(a + 1, a + 1 + n);
	for(int i = 1 ; i <= n ; ++ i)
		sa[i] = sa[i - 1] + a[i];
	
	for(int i = 1 ; i <= n ; ++ i) b[i] = io();
	reverse(b + 1, b + 1 + n);
	for(int i = 1 ; i <= n ; ++ i)
		sb[i] = sb[i - 1] + b[i], t[i] = (i == 1 ? sb[1] - 1 * w : max(sb[i] - i * w, t[i - 1]));
	
	ans = min(a[1], b[1]) - (1 + 1) * w;
	for(int i = 1, j1 = 0, j2 = 0 ; i <= n ; ++ i) {
		// s[j] <= s[i]
		if(sb[n] <= sa[i]) {
			while(j1 + 1 <= n && sb[j1 + 1] <= sa[i]) ++ j1;
			if(j1 <= n && sb[j1] <= sa[i]) {
				ans = max(ans, t[j1] - i * w);
			}
		}
		
		// s[j] >= s[i]
		while(j2 + 1 <= n && sb[j2] < sa[i]) ++ j2;
		if(j2 <= n) {
			ans = max(ans, calc(i, j2));
		}
	}
	io(ans);
}
