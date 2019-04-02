#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 22;
ll ans;
int a[30][30], n, m, sta[30], top;
ll f[N][N];
ll pak[1 << N];
bool col_safe[30][1 << N];

// 预处理(i,j)的关系
int rel[30][30];

int main() {
// #ifdef ONLINE_JUDGE
//     freopen("submatrix.in", "r", stdin);
//     freopen("submatrix.out", "w", stdout);
// #endif
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i < n ; ++ i) {
        for(int j = 0 ; j < m ; ++ j) {
            scanf("%d", &a[i][j]);
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        for(int s = 1 ; s < (1 << m) ; ++ s) {
            top = 0;
            for(int j = 0 ; j < m ; ++ j) {
                if((s >> j) & 1) {
                    sta[++ top] = a[i][j];
                }
            }
            col_safe[i][s] =
                is_sorted(sta + 1, sta + 1 + top) ||
                is_sorted(sta + 1, sta + 1 + top, greater<int> ());
        }
    }

    for(int i = 0 ; i < n ; ++ i) {
        for(int j = 0 ; j < n ; ++ j) {
            for(int k = 0 ; k < m ; ++ k) {
                rel[i][j] |= (a[i][k] < a[j][k]) << k;
            }
        }
    }

    for(int i = 0 ; i < n ; ++ i) {
        for(int s = 1 ; s < (1 << m) ; ++ s) {
            if(col_safe[i][s]) {
                ++ ans;
            }
        }
    }

    for(int s = 1 ; s < (1 << m) ; ++ s) {
        for(int i = 0 ; i < n ; ++ i) {
            for(int j = 0 ; j < i ; ++ j) {
                f[i][j] = 0;
            }
        }
        for(int i = 0 ; i < n ; ++ i) {
            // 感觉这里有点问题，可能会把不合法的统计进去？
            if(col_safe[i][s]) {
                for(int j = 0 ; j < i ; ++ j) {
                    f[i][j] += col_safe[j][s];
                    pak[rel[j][i] & s] += f[i][j];
                }
                for(int k = i + 1 ; k < n ; ++ k) {
                    f[k][i] += pak[rel[i][k] & s];
                }
                for(int j = 0 ; j < i ; ++ j) {
                    pak[rel[j][i] & s] = 0;
                    ans += f[i][j];
                }
            }
        }
    }

    printf("%lld\n", ans);
}
