#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 3e5 + 10, p = 998244353;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
    return r;
}
ll fac[N], invfac[N], n, a, b, k;
ll C(ll x, ll n) {
    return fac[n] * invfac[x] % p * invfac[n - x] % p;
}
int main() {
    scanf("%lld%lld%lld%lld", &n, &a, &b, &k);
    for(ll i = fac[0] = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % p;
    for(ll i = 0 ; i <= n ; ++ i) invfac[i] = pw(fac[i], p - 2);
    ll ans = 0;
    for(ll i = 0 ; i <= n ; ++ i) {
        if(k - i * a >= 0 && (k - i * a) % b == 0 && (k - i * a) / b <= n) {
            ans = (ans + C(i, n) * C((k - i * a) / b, n) % p) % p;
        }
    }
    printf("%lld\n", ans);
}
