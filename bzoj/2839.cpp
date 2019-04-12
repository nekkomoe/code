#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e6 + 10, mod = 1e9 + 7;

int n, k;
ll fac[N], invfac[N];
ll pw(ll a, ll b, ll mod) {
    ll r = 1;
    for( ; b ; b /= 2, a = a * a % mod) {
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
    scanf("%d%d", &n, &k);
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2, mod);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    ll ans = 0;
    for(int i = k ; i <= n ; ++ i) {
        ans = (ans +
            C(n, i) * (pw(2, pw(2, n - i, mod - 1), mod) - 1) % mod * ((i - k) & 1 ? -1 : 1) * C(i, k) % mod
        ) % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
