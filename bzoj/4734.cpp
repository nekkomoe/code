#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, mod = 998244353;

const int g[2] = { 3, (mod + 1) / 3 };

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll f[N];
void ntt(ll *a, int n, int ty) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];

    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % mod;
                f[k] = (u + v) % mod;
                f[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }

    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty) a[i] = a[i] * inv % mod;
    }
}

int m; ll n, x, a[N], e[N], fac[N], invfac[N];

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

int main() {
    scanf("%lld%d%lld", &n, &m, &x), ++ m;
    int len = 1; while(len <= 2 * m) len <<= 1;
    init(len);

    for(int i = 0 ; i < m ; ++ i) {
        scanf("%lld", &a[i]);
        a[i] = a[i] * invfac[i] % mod;
    }
    for(int i = 0 ; i < m ; ++ i) {
        e[i] = i & 1 ? -invfac[i] : invfac[i];
    }
    ntt(a, len, 0), ntt(e, len, 0);
    for(int i = 0 ; i < len ; ++ i) {
        a[i] = a[i] * e[i] % mod;
    }
    ntt(a, len, 1);

    ll ans = 0;

    ll prod = 1;
    for(int i = 0 ; i < m ; ++ i) {
        ans = (ans + a[i] * prod) % mod;
        prod = prod * (n - i) % mod * x % mod;
    }

    printf("%lld\n", (ans + mod) % mod);
}
