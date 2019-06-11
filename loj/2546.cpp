#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10, K = 110;

int n, k;
vector<int> g[N];
int f[N][K][2][2], sz[N], h[K][2][2];
void upd(int &x, int y) {
    x = ((ll) x + y) % mod;
}
void dfs(int u, int fa) {
    f[u][0][0][0] = f[u][1][1][0] = 1;
    sz[u] = 1;
    for(int v: g[u]) {
        if(v == fa) {
            continue;
        }
        dfs(v, u);

        for(int i = 0 ; i <= min(k, sz[u]) ; ++ i) {
            for(int j = 0 ; j <= min(k, sz[v]) && i + j <= k ; ++ j) {
                
                // 1
                upd(h[i + j][0][0], (ll) f[u][i][0][0] * f[v][j][0][1] % mod);
                upd(h[i + j][0][1], (ll) f[u][i][0][0] * f[v][j][1][1] % mod);

                // 2
                upd(h[i + j][0][1], (ll) f[u][i][0][1] * (f[v][j][0][1] + f[v][j][1][1]) % mod);

                // 3
                upd(h[i + j][1][0], (ll) f[u][i][1][0] * (f[v][j][0][0] + f[v][j][0][1]) % mod);
                upd(h[i + j][1][1], (ll) f[u][i][1][0] * (f[v][j][1][0] + f[v][j][1][1]) % mod);

                // 4
                upd(h[i + j][1][1], (ll) f[u][i][1][1] * (
                    (ll) f[v][j][0][0] + f[v][j][0][1]
                  + f[v][j][1][0] + f[v][j][1][1]
                ) % mod);
            }
        }

        sz[u] += sz[v];
        for(int i = 0 ; i <= min(k, sz[u]) ; ++ i) {
            for(int a = 0 ; a < 2 ; ++ a) {
                for(int b = 0 ; b < 2 ; ++ b) {
                    f[u][i][a][b] = h[i][a][b];
                    h[i][a][b] = 0;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    printf("%lld\n", ((f[1][k][0][1] + f[1][k][1][1]) % mod + mod) % mod);
}
