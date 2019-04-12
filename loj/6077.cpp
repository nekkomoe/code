#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 7, m = 450;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
int f[N][m + 10], n, k;
ll fac[int(2e6) + 10], invfac[int(2e6) + 10];
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
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

int main() {
    scanf("%d%d", &n, &k);
    f[0][0] = 1;
    for(int i = 1 ; i <= k ; ++ i) {
        for(int j = 1 ; j <= min(i, m) ; ++ j) {
            f[i][j] = ((ll) f[i - j][j - 1] + f[i - j][j]) % mod;
            if(i > n) {
                (f[i][j] -= f[i - n - 1][j - 1]) %= mod;
            }
        }
    }
    
    init(int(2e6));

    ll ans = 0;
    for(int i = 0 ; i <= k ; ++ i) {

        ll res = 0;
        for(int j = 0 ; j <= min(i, m) ; ++ j) {
            res += f[i][j] * (j & 1 ? -1 : 1) % mod;
            res %= mod;
        }
        ans += res * C(n - 1 + k - i, n - 1) % mod;
        if(res < 0) res += mod;
        ans %= mod;
    }

    if(ans < 0) {
        ans += mod;
    }
    printf("%lld\n", ans);
}
