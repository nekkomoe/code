#include <bits/stdc++.h>
using namespace std; typedef long long ll;
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
    inline void space(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

const int N = 2e6 + 10;
int n, a[N]; ll ans;
int tmp[N];

void sol(int l, int r) {
	if(l >= r) return ;
	int mid = (l + r) >> 1;
	sol(l, mid), sol(mid + 1, r);
	int x = l, y = mid + 1, top = 0;
	while(x <= mid && y <= r) {
		if(a[x] > a[y]) {
			ans += mid - x + 1;
			tmp[++ top] = a[y ++];
		} else {
			tmp[++ top] = a[x ++];
		}
	}
	while(x <= mid) tmp[++ top] = a[x ++];
	while(y <= r) tmp[++ top] = a[y ++];;
	for(int i = l ; i <= r ; ++ i) a[i] = tmp[i - l + 1];
}

int main() {
	n = io();
	for(int i = 1 ; i <= n ; ++ i) a[i] = io();
	sol(1, n);
	io(ans);
}
