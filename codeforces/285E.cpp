#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010, mod = 1000000007;
int n, k;
ll C[N][N], f[N][N][2][2], g[N], h[N], fac[N];

int main() {
    // freopen("rank.in", "r", stdin);
    // freopen("rank.out", "w", stdout);
    scanf("%d%d", &n, &k);
    C[0][0] = fac[0] = 1;
    for(int i = 1 ; i < 1010 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j < 1010 ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
        fac[i] = fac[i - 1] * i % mod;
    }
    f[0][0][1][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        f[i][0][0][0] = (f[i - 1][0][0][0] + f[i - 1][0][1][0]) % mod;
        for(int j = 1 ; j <= i ; ++ j) {
            for(int k = 0 ; k <= 1 ; ++ k) {
                f[i][j][k][0] = (f[i - 1][j][0][k] + f[i - 1][j][1][k] + f[i - 1][j - 1][0][k]) % mod;
                f[i][j][k][1] = (f[i - 1][j - 1][0][k] + f[i - 1][j - 1][1][k]) % mod;
//				printf("%lld %lld\n", f[i][j][k][0], f[i][j][k][1]);
            }
        }
    }
    
    for(int i = 0 ; i <= n ; ++ i) {
        g[i] = (f[n][i][1][0] + f[n][i][0][0]) % mod * fac[n - i] % mod;
    }
    for(int i = 0 ; i <= n ; ++ i)
        for(int j = i ; j <= n ; ++ j)
            h[i] = (h[i] + ((j - i) % 2 ? -1 : 1) * C[j][i] * g[j]) % mod;
    printf("%lld\n", (h[k] % mod + mod) % mod);
}
