#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 10;

int n, m, cnt[N], f[N][5][5];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        ++ cnt[x];
    }
    for(int i = 0 ; i <= min(4, cnt[1]) ; ++ i) {
        f[1][i][0] = (cnt[1] - i) / 3;
    }
    for(int i = 2 ; i <= m ; ++ i) {
        for(int j = 0 ; j <= 4 ; ++ j) {
            for(int k = 0 ; k <= 4 ; ++ k) {
                for(int l = 0 ; l <= 2 ; ++ l) {
                    if(j <= cnt[i]
                    && k <= cnt[i - 1]
                    && j + l <= cnt[i]
                    && k + l <= cnt[i - 1]
                    && l <= cnt[i - 2]
                    && k + l <= 4) {
                        f[i][j][k] = max(f[i][j][k], f[i - 1][k + l][l] + (cnt[i] - l - j) / 3 + l);
                    }
                }
            }
        }
    }
    printf("%d\n", f[m][0][0]);
}
