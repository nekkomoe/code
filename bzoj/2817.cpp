#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define range [2][101][9001][3]
#define OFFSET 4500
int n, m, k;
 
double ld_f range;
 
#ifdef ONLINE_JUDGE
__float128 flt_f range;
#else
double flt_f range;
#endif
 
template<typename T> void print(T x) {
    // cout << fixed << setprecision(k) << x << endl;
    printf("0.");
    for(int i = 1 ; i <= k ; ++ i) {
        x *= 10;
        printf("%d", int(x + (i == k) * 0.5));
        x -= int(x);
    }
}
 
template<typename T> void sol(T f range) {
    T ans = 0;
    int cur = 0;
    f[0][0][OFFSET][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        cur ^= 1;
        memset(f[cur], 0, sizeof f[cur]);
        for(int j = 0 ; j <= i - 1 ; ++ j) {
            for(int k = 0 ; k <= 9000 ; ++ k) {
                for(int l = 0 ; l <= 2 ; ++ l) {
                    if(l != 2) {
                        // 可以放在两侧
                        if(k - i >= 0) {
                            f[cur][j + 1][k - i][l + 1] += f[!cur][j][k][l] * (2 - l);
                        }
                        if(j && k + i <= 9000) {
                            f[cur][j][k + i][l + 1] += f[!cur][j][k][l] * (2 - l);
                        }
                    }
                    if(j >= 2 && k + 2 * i <= 9000) {
                        // 可以合并两个块
                        f[cur][j - 1][k + 2 * i][l] += f[!cur][j][k][l] * (j - 1);
                    }
                    if(k - 2 * i >= 0) {
                        // 独自成为一个块
                        f[cur][j + 1][k - 2 * i][l] += f[!cur][j][k][l] * (j + 1 - l);
                    }
                    if(j) {
                        // 只与一个块相邻
                        f[cur][j][k][l] += f[!cur][j][k][l] * (2 * j - l);
                    }
                }
            }
        }
    }
    for(int i = OFFSET + m ; i <= 9000 ; ++ i) ans += f[cur][1][i][2];
    for(int i = 1 ; i <= n ; ++ i) ans /= i;
    print(ans);
}
 
int main() {
    scanf("%d%d%d", &n, &m, &k);
    m = min(m, 9000);
    if(k <= 8) {
        sol(ld_f);
    } else {
        sol(flt_f);
    }
}
