#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2010, mod = 1e9 + 9;

int n, k, a[N], b[N], R[N];
ll f[N][N], g[N], fac[N], invfac[N], ans;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    scanf("%d%d", &n, &k);
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i >= 1 ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &b[i]);
    sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n && b[j] < a[i] ; ++ j) {
            ++ R[i];
        }
    }
    f[0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= i ; ++ j) {
            f[i][j] = (f[i - 1][j] + (j ? (R[i] - (j - 1)) * f[i - 1][j - 1] : 0)) % mod;
        }
    }
    for(int i = 0 ; i <= n ; ++ i) {
        g[i] = f[n][i] * fac[n - i] % mod;
    }
    if((n + k) % 2) puts("0");
    else {
        k = (n + k) / 2; ll ans = 0;
        for(int i = k ; i <= n ; ++ i) {
            (ans += ((i - k) & 1 ? -1 : 1) * C(i, k) * g[i] % mod) %= mod;
        }
        printf("%lld\n", (ans + mod) % mod);
    }
}
