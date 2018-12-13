#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 110;

int head[N], rest[N * 2], to[N * 2], tot, n, k;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int f[N][N], g[N][N];

void dfs(int u, int fa) {
    for(int i = 0 ; i <= k ; ++ i) f[u][i] = g[u][i] = 1;
    for(int _ = head[u] ; _ ; _ = rest[_]) {
        int v = to[_];
        if(v == fa) continue;
        dfs(v, u);
        for(int i = k ; i > 0 ; -- i) {
            for(int j = 0 ; j < i ; ++ j) {
                if(i - j >= 2) {
                    f[u][i] = max(f[u][i], f[v][j] + f[u][i - j - 2]);
                    g[u][i] = max(g[u][i], f[v][j] + g[u][i - j - 2]);
                }
                g[u][i] = max(g[u][i], g[v][j] + f[u][i - j - 1]);
            }
        }
    }
    for(int i = 1 ; i <= k ; ++ i) {
        f[u][i] = max(f[u][i], f[u][i - 1]);
        g[u][i] = max(g[u][i], g[u][i - 1]);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v), ++ u, ++ v;
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    printf("%d\n", g[1][k]);
} 

