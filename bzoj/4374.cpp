#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 1e5, mod = 1e9 + 7;

int f[10][N + 5], g[N + 5], n, d, a[N], sum;

int main() {
    scanf("%d%d", &n, &d);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        sum ^= a[i];
    }
    sort(a + 1, a + 1 + n);
    f[0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        int lim = min(N, 2 * a[i]);
        for(int j = 0 ; j <= lim ; ++ j) {
            g[j] = (f[0][j] + f[d - 1][j ^ a[i]]) % mod;
        }
        for(int k = d - 1 ; k ; -- k) {
            for(int j = 0 ; j <= lim ; ++ j) {
                (f[k][j] += f[k - 1][j ^ a[i]]) %= mod;
            }
        }
        for(int j = 0 ; j <= lim ; ++ j) {
            f[0][j] = g[j];
        }
    }
    int ans = ((f[0][sum] - (n % d == 0)) % mod + mod) % mod;
    printf("%d\n", ans);
}
