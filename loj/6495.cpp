#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 30, nek[] = { 0, 1, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6 };

int mod, n, C[N][N];
ll f[N][N];
ll getc(int n, int m) {
    return n < m || m < 0 ? 0 : C[n][m];
}
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
int main() {
    scanf("%d%d", &n, &mod);
    C[0][0] = 1;
    for(int i = 1 ; i < N ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= i ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    f[1][1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        for(int j = 2 ; j <= i ; ++ j) {
            for(int x = 1 ; x <= i ; ++ x) {
                for(int y = 1 ; y <= j - 2 ; ++ y) {
                    f[i][j] += f[i - x][j] * f[x][y] % mod * getc(i - 2, x - 1) % mod;
                }
                for(int y = 1 ; y <= j ; ++ y) {
                    f[i][j] += f[i - x][y] * f[x][j - 1] % mod * getc(i - 2, x - 1) % mod;
                }
            }
        }
    }
    ll fac = 1;
    for(int i = 1 ; i < n ; ++ i) (fac *= i) %= mod;
    fac = pw(fac, mod - 2);
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) ans = (ans + (ll) f[n][i] * i % mod) % mod;
    ans = ans * fac % mod;
    if(ans < 0) ans += mod;
    printf("%d\n%lld\n", nek[n], ans);
}
