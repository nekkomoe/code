#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, mod = 1e9 + 7;

int n, m, k, x;
ll f[N][11][3], mem[11][3];
vector<int> g[N];

void dfs(int u, int fa) {
    f[u][0][0] = k - 1;
    f[u][1][1] = 1;
    f[u][0][2] = m - k;
    for(int v: g[u]) {
        if(v == fa) continue ;
        dfs(v, u);
        memset(mem, 0, sizeof mem);
        for(int a = 0 ; a <= x ; ++ a) {
            for(int b = 0 ; a + b <= x ; ++ b) {
                (mem[a + b][0] += f[u][a][0] * (f[v][b][0] + f[v][b][1] + f[v][b][2]) % mod) %= mod;
                (mem[a + b][1] += f[u][a][1] * (f[v][b][0]) % mod) %= mod;
                (mem[a + b][2] += f[u][a][2] * (f[v][b][0] + f[v][b][2]) % mod) %= mod;
            }
        }
        memcpy(f[u], mem, sizeof f[u]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    scanf("%d%d", &k, &x);
    dfs(1, 0);
    ll ans = 0;
    for(int i = 0 ; i <= x ; ++ i) {
        for(int j = 0 ; j <= 2 ; ++ j) {
            (ans += f[1][i][j]) %= mod;
        }
    }
    printf("%lld\n", ans);
}
