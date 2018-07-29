#include "bits/stdc++.h"
using namespace std;
int n, d, k;
int ans[1010][1010];
int main() {
    scanf("%d%d%d", &n, &k, &d);
    for(int i = 1 ; i <= d ; ++ i) ans[1][i] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= d ; ++ j) ans[i][j] = ans[i - 1][j];
        ++ ans[i][1];
        for(int j = 1 ; j <= d ; ++ j) {
            if(ans[i][j] > k) {
                ans[i][j] = 1;
                ++ ans[i][j + 1];
            }
        }
        if(ans[i][d + 1]) {
            puts("-1");
            exit(0);
        }
    }
    for(int i = 1 ; i <= d ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            printf("%d ", ans[j][i]);
        }
        puts("");
    }
}
