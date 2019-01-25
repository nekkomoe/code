#include "bits/stdc++.h"
using namespace std;

const int N = 510;

int n, m, a[N][N], b[N][N];

int sol(int a[N][N]) {
    for(int k = 1 ; k <= n ; ++ k)
        for(int i = 1 ; i <= n ; ++ i)
            for(int j = 1 ; j <= n ; ++ j)
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
    return a[1][n];
}

int main() {
    scanf("%d%d", &n, &m);
    memset(a, 0x3f, sizeof a);
    memset(b, 0x3f, sizeof b);
    for(int i = 1 ; i <= n ; ++ i) a[i][i] = b[i][i] = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        if(u == v) continue;
        a[u][v] = a[v][u] = 1;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(i != j && a[i][j] == 0x3f3f3f3f) {
                b[i][j] = b[j][i] = 1;
            }
        }
    }
    int ans = max(sol(a), sol(b));
    if(ans >= 0x3f3f3f3f) ans = -1;
    printf("%d\n", ans);
}

