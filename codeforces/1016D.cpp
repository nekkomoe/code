#include "bits/stdc++.h"
using namespace std;
const int N = 110;
int n, m, a[N], b[N], ans[N][N];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= m ; ++ i) scanf("%d", &b[i]);
    for(int i = 1 ; i <= n ; ++ i) ans[i][m] = a[i];
    for(int j = 1 ; j <= m ; ++ j) ans[n][j] = b[j];
    int t = 0;
    for(int i = 1 ; i < m ; ++ i) t ^= b[i];
    ans[n][m] = t ^ a[n];
    t = 0;
    for(int i = 1 ; i < n ; ++ i) t ^= a[i];
    if((t ^ b[m]) != ans[n][m]) {
        puts("NO");
    } else {
        puts("YES");
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= m ; ++ j) {
                printf("%d ", ans[i][j]);
            }
            puts("");
        }
    }
}
