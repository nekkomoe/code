#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5e5 + 10, mod = 19491001;

ll n, k, d, res, fac[N], invfac[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    cin >> n >> k >> d;
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= k ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[k] = pw(fac[k], mod - 2);
    for(int i = k - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    if(d == 1) {
        res = pw(k, n);
    } else if(d == 2) {
        for(int i = 0 ; i <= k ; ++ i) {
            res = (res + C(k, i) * pw(2 * i - k, n) % mod * pw(2, (ll) k * (mod - 2) % (mod - 1)) % mod);
        }
    } else {
        ll wn = pw(7, (mod - 1) / 3);
        ll w[3] = { 1, wn, wn * wn % mod };
        for(int i = 0 ; i <= k ; ++ i) {
            for(int j = 0 ; i + j <= k ; ++ j) {
                ll val = (ll) i + (w[1] * j % mod) % mod + (w[2] * (k - i - j) % mod) % mod;
                val %= mod;
                res = (res + C(k, i) * C(k - i, j) % mod * pw(val, n) % mod) % mod;
            }
        }
        res = res * pw(3, (ll) k * (mod - 2) % (mod - 1)) % mod;
    }
    printf("%lld\n", (res % mod + mod) % mod);
}
