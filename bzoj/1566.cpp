#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 510, mod = 1024523;

ll f[2][N][N]; int p, n, m;
char a[N], b[N];

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s%s", a + 1, b + 1);
    f[0][0][0] = 1;
    for(int i = 0 ; i <= n ; ++ i, p ^= 1) {
        for(int j = 0 ; j <= m ; ++ j) {
            for(int k = 0 ; k <= n ; ++ k) {
                int l = i + j - k, tmp = f[p][j][k];
                if(0 <= l && l <= m) {
                    if(a[i + 1] == a[k + 1]) {
                        (f[!p][j][k + 1] += tmp) %= mod;
                    }
                    if(a[i + 1] == b[l + 1]) {
                        (f[!p][j][k] += tmp) %= mod;
                    }
                    if(b[j + 1] == a[k + 1]) {
                        (f[p][j + 1][k + 1] += tmp) %= mod;
                    }
                    if(b[j + 1] == b[l + 1]) {
                        (f[p][j + 1][k] += tmp) %= mod;
                    }
                }
                f[p][j][k] = 0;
            }
        }
    }
    printf("%lld\n", (f[p][m][n] % mod + mod) % mod);
}
