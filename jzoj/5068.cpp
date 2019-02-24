#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1004535809, N = 110;

int n, a[N];
ll f[N][N][N], fac[N], invfac[N];

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
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    f[0][0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        f[i][0][0] = 1;
        for(int j = 1 ; j <= i ; ++ j) {
            for(int k = 0 ; k <= n - 2 ; ++ k) {
                f[i][j][k] = f[i - 1][j][k];
                for(int t = 1 ; t <= min(k + 1, a[i]) ; ++ t) {
                    (f[i][j][k] += C(k, t - 1) * f[i - 1][j - 1][k - (t - 1)] % mod) %= mod;
                }
            }
        }
    }
    printf("%d ", n);
    for(int i = 2 ; i <= n ; ++ i) {
        printf("%lld ", f[n][i][i - 2]);
    }
}
