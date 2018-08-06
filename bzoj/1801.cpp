#include <cstdio>
const long long mod = 9999973LL;
long long f[110][110][110], ans;
int n, m;
long long C(long long x) {return x * (x - 1) / 2;}
int main() {
    scanf("%d%d", &n, &m);
    f[0][0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= m ; ++ j) {
            for(int k = 0 ; k <= m - j ; ++ k) {
                f[i][j][k] = f[i - 1][j][k];
                if(j > 0) f[i][j][k] += f[i - 1][j - 1][k] * (m - j - k + 1);
                if(j > 1) f[i][j][k] += f[i - 1][j - 2][k] * C(m - j - k + 2);
                if(k > 0 && j < m) f[i][j][k] += f[i - 1][j + 1][k - 1] * (j + 1);
                if(k > 0 && j > 0) f[i][j][k] += f[i - 1][j][k - 1] * (m - j - k + 1) * j;
                if(k > 1 && j < m - 1) f[i][j][k] += f[i - 1][j + 2][k - 2] * C(j + 2);
                f[i][j][k] %= mod;
            }
        }
    }
    for(int i = 0 ; i <= m ; ++ i) {
        for(int j = 0 ; j <= m - i ; ++ j) {
            ans += f[n][i][j];
            ans %= mod;
        }
    }
    printf("%lld\n", ans);
}
