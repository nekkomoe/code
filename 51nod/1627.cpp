#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 1000000007;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int n, m; ll fac[N], invfac[N];
ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    scanf("%d%d", &n, &m);
    int x = max(n, m);
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= x ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[x] = pw(fac[x], mod - 2);
    for(int i = x - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    ll ans = 0;
    for(int i = 1 ; i <= min(n, m) - 1 ; ++ i) {
        ans = (ans + C(n - 2, i - 1) * C(m - 2, i - 1) % mod) % mod;
    }
    printf("%lld\n", ans);
}
