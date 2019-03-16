#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 1e9 + 7;
ll fac[N], invfac[N];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b > 0 ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}
int main() {
    int n, k; scanf("%d%d", &n, &k);
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    ll ans = 0, p = 0; for(int i = 1, x ; i <= n ; ++ i) scanf("%d", &x), ans = (ans + x) % mod;
    for(int i = 0 ; i <= k - 1 ; ++ i) {
        ll x = pw(-1, i) * pw(k - i, n - 2) % mod * (k - i + n - 1) % mod;
        ll y = fac[i] * fac[k - 1 - i] % mod;
        p = (p + x * pw(y, mod - 2) % mod) % mod;
    } ans = ans * p % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
}
