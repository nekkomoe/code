#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3e5 + 10;

int n, q;
vector<int> g[N];
int fa[N][21], dep[N];
ll sz[N];

ll f[N];
ll s_f[N]; // u~root的f之和

ll h[N];
ll s_h[N];

void dfs(int u) {
    dep[u] = dep[fa[u][0]] + 1;
    
    sz[u] = 1;
    f[u] = 1;

    for(int i = 1 ; i <= 20 ; ++ i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }

    for(int v: g[u]) {
        if(v != fa[u][0]) {
            fa[v][0] = u;
            dfs(v);
            f[u] += sz[v] * sz[u];
            sz[u] += sz[v];
        }
    }
}

void getsumfh(int u) {
    h[u] = sz[u] * (sz[fa[u][0]] - sz[u]);
    s_f[u] = s_f[fa[u][0]] + f[u];
    s_h[u] = s_h[fa[u][0]] + h[u];
    for(int v: g[u]) {
        if(v != fa[u][0]) {
            getsumfh(v);
        }
    }
}

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

ll calc_chain(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    ll res = 0;
    res += s_f[u] - s_f[fa[v][0]];
    res -= s_h[u] - s_h[v];
    return res;
}
int get_son(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] > dep[v]) {
            u = fa[u][i];
        }
    }
    return u;
}

void runprog() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        g[i].clear();
        for(int j = 1 ; j <= 20 ; ++ j) {
            fa[i][j] = 0;
        }
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1);
    getsumfh(1);
    while(q --) {
        int u, v; scanf("%d%d", &u, &v);
        if(dep[u] < dep[v]) swap(u, v); // u 比较深
        int lca = getlca(u, v);
        if(lca == v) {
            ll ans = calc_chain(u, v);
            if(u == v) {
                ans += (n - sz[u]) * sz[u];
            } else {
                int w = get_son(u, v);
                // printf("w = %d\n", w);
                // printf("%lld + %lld\n", ans, (n - sz[v]) * (sz[v] - sz[w]));
                ans += (n - sz[v]) * (sz[v] - sz[w]);
            }
            printf("%lld\n", ans);
        } else {
            int x = get_son(u, lca);
            int y = get_son(v, lca);
            ll ans = calc_chain(u, x) + calc_chain(v, y);
            int z = lca;
            ans +=
                f[z] - sz[x] * sz[y] - (sz[x] + sz[y]) * (sz[z] - sz[x] - sz[y])
                + (sz[z] - sz[x] - sz[y]) * (n - sz[z]);
            printf("%lld\n", ans);
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
