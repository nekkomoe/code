// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 };

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

const int N = 5e6 + 10;
ll a[N], b[N], f[N], ans;
inline int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
inline void ntt(ll *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) {
        f[rev(i, n)] = a[i];
    }
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
        if(ty) {
            a[i] = a[i] * inv % mod;
        }
    }
}

ll fac[N], invfac[N];
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}

ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    int D, n, m;
    scanf("%d%d%d", &D, &n, &m);
    int k = min(D, n - 2 * m), d = D - 1;
    init(N - 1);
    for(int i = 0 ; i <= k ; ++ i) {
        a[i] = ((k - i) & 1 ? -1 : 1) * invfac[i] * invfac[k - i] % mod;
    }
    for(int i = 0 ; i <= min(d, d - k) ; ++ i) {
        b[i] = invfac[i] * invfac[d - k - i] % mod;
    }

    int len = 1;
    while(len <= 2 * (D + 10)) len <<= 1;
    ntt(a, 0, len), ntt(b, 0, len);
    for(int i = 0 ; i < len ; ++ i) {
        a[i] = a[i] * b[i] % mod;
    }
    ntt(a, 1, len);
    for(int i = 0 ; i <= D ; ++ i) {
        ll res = 0;
        if(i == D) {
            for(int j = 0 ; j <= k ; ++ j) {
                res += C(D, j);
                res %= mod;
            }
        } else {
            res = fac[i] * fac[d - i] % mod * a[i] % mod;
        }
        ans += C(D, i) * pw(2 * i - D, n) % mod * res % mod;
        ans %= mod;
    }

    ans = ans * pw((mod + 1) / 2, D) % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
}
