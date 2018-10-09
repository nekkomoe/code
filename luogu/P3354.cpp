#include <bits/stdc++.h>
using namespace std;
const int N = 110, K = 60;
struct E { int v, w; };
vector<E> p[N];
int f[N][N][K], g[N][N][K], n, k, sta[N], top, dep[N], w[N];

void dfs(int u) {
    sta[++ top] = u;

    for(E e: p[u]) {
        int v = e.v;
        dep[v] = dep[u] + e.w;
        dfs(v);
        for(int i = 1 ; i <= top ; ++ i) {
            int z = sta[i];
            for(int j = k ; ~ j ; -- j) {
                f[u][z][j] += f[v][z][0];
                g[u][z][j] += f[v][u][0];
                for(int t = j ; ~ t ; -- t) {
                    f[u][z][j] = min(f[u][z][j], f[u][z][j - t] + f[v][z][t]);
                    g[u][z][j] = min(g[u][z][j], g[u][z][j - t] + f[v][u][t]);
                }
            }
        }
    }

    for(int i = 1 ; i <= top ; ++ i) {
        int z = sta[i];
        for(int j = k ; ~ j ; -- j) {
            if(j) {
                f[u][z][j] = min(g[u][z][j - 1], f[u][z][j] + w[u] * (dep[u] - dep[z]));
            } else {
                f[u][z][j] += w[u] * (dep[u] - dep[z]);
            }
        }
    }

    -- top;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        int v, d;
        scanf("%d%d%d", &w[i], &v, &d);
        p[v].push_back((E) { i, d });
    }
    dfs(0);
    printf("%d\n", f[0][0][k]);
}