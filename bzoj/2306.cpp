#include "bits/stdc++.h"
using namespace std;
typedef long double ld;
const int N = 210;
const ld inf = 1e30;

int n, m, v0;

ld w[N], p, f[N][N], g[N][N], ans;

int main() {
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i) cin >> w[i];
    cin >> v0 >> p;
    for(int i = 0 ; i <= n ; ++ i)
        for(int j = 0 ; j <= n ; ++ j)
            f[i][j] = -inf;
    for(int i = 1 ; i <= n ; ++ i)
        f[i][i] = 0;
    for(int i = 1, u, v ; i <= m ; ++ i) {
        cin >> u >> v;
        f[u][v] = w[v] * p;
    }
    for(ld cnt = p ; cnt > (ld) 1e-8 ; cnt *= cnt) {
        for(int i = 1 ; i <= n ; ++ i)
            for(int j = 1 ; j <= n ; ++ j)
                g[i][j] = -inf;
        for(int k = 1 ; k <= n ; ++ k)
            for(int i = 1 ; i <= n ; ++ i)
                for(int j = 1 ; j <= n ; ++ j)
                    g[i][j] = max(g[i][j], f[i][k] + f[k][j] * cnt);
        memcpy(f, g, sizeof g);
    }
    for(int i = 1 ; i <= n ; ++ i) ans = max(ans, f[v0][i]);
    printf("%.1Lf", ans + w[v0]);
}
