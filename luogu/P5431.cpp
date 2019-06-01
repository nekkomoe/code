// luogu-judger-enable-o2
#include "bits/stdc++.h"
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

const int N = 5e6 + 10;

int a[N], inv[N], prod[N], n, mod, k;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int main() {
    n = io(), mod = io(), k = io();
    prod[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = io();
        prod[i] = (ll) prod[i - 1] * a[i] % mod;
    }

    inv[n] = pw(prod[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        inv[i] = (ll) inv[i + 1] * a[i + 1] % mod;
    }
    ll ans = 0, pw = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        if((pw *= k) >= mod) pw %= mod;
        ans = (ans + (ll) inv[i] * prod[i - 1] % mod * pw % mod) % mod;
    }
    printf("%lld\n", ans);
}
