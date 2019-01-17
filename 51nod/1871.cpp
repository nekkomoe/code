#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1 << 22;
int n, t; ll a[N], b[N];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
const ll inv2 = pw(2, mod - 2);

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
        wchar(' ');
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

void fwt(ll *f, int n, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1)
        for(int j = 0 ; j + i / 2 < n ; j += i)
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) f[k] = (u + v) % mod, f[k + i / 2] = (u - v) % mod;
                else f[k] = (u + v) * inv2 % mod, f[k + i / 2] = (u - v) * inv2 % mod;
            }
}

int main() {
    n = io(), t = io();
    n = 1 << n;
    for(int i = 0 ; i < n ; ++ i) a[i] = !io;
    b[0] = 1; for(int i = 1 ; i < n ; i <<= 1) b[i] = 1;
    fwt(b, n, 0), fwt(a, n, 0);
    for(int i = 0 ; i < n ; ++ i) a[i] = a[i] * pw(b[i], t) % mod;
    fwt(a, n, 1);
    for(int i = 0 ; i < n ; ++ i) io((a[i] + mod) % mod);
}

