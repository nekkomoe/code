// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
const int N = 1e6 + 10, mod = 1e9 + 7;

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

int n, m;
ll mu[N], fib[N], fibinv[N], f[N], invf[N];
int vis[N], pri[N], tot;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll calc(int l, int r) {
    if(l == 1) return f[r];
    else return f[r] * invf[l - 1] % mod;
}

int qx[N], qy[N];

int main() {
    int T = io(), mx = 0;
    for(int i = 1 ; i <= T ; ++ i) {
        int n = io(), m = io(); if(n > m) swap(n, m);
        qx[i] = n, qy[i] = m;
        mx = max(mx, qx[i]);
    }
    
    fib[0] = 0, fib[1] = 1, fibinv[1] = 1;
    for(int i = 2 ; i <= mx ; ++ i) fib[i] = (fib[i - 1] + fib[i - 2]) % mod, fibinv[i] = pw(fib[i], mod - 2);
    
    mu[1] = 1;
    for(int i = 2 ; i <= mx ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= mx ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    }
    for(int i = 1 ; i <= mx ; ++ i) f[i] = 1; 
    for(int i = 1 ; i <= mx ; ++ i) {
        for(int j = 1 ; j * i <= mx ; ++ j) {
            (f[i * j] *= (mu[j] == 1 ? fib[i] : mu[j] == 0 ? 1 : fibinv[i])) %= mod;
        }
    }
    f[0] = 1;
    for(int i = 1 ; i <= mx ; ++ i) {
        f[i] = f[i - 1] * f[i] % mod;
        invf[i] = pw(f[i], mod - 2);
    }
    
    for(int i = 1 ; i <= T ; ++ i) {
        int n = qx[i], m = qy[i];
        ll ans = 1;
        for(int i = 1, j ; i <= n ; i = j + 1) {
            j = min(n / (n / i), m / (m / i));
            ans = ans * pw(calc(i, j), (ll) (n / i) * (ll) (m / i)) % mod;
        }
        io(ans < 0 ? ans + mod : ans);
    }
} 
