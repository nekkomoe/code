#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1000010 * 2;

int head[N], rest[N], to[N], tot, dfn[N], par[N][30], n, q, k, deep[N], sta[N], top, vis[N], bak[N];

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u, int fa) {
    dfn[u] = ++ *dfn;
    deep[u] = deep[fa] + 1;
    par[u][0] = fa;
    for(int j = 1 ; j <= 25 ; ++ j) par[u][j] = par[par[u][j - 1]][j - 1];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            dfs(v, u);
        }
    }
}

bool cmp(int a, int b) {
    return dfn[a] < dfn[b];
}

int getlca(int u, int v) {
    if(deep[u] < deep[v]) swap(u, v);
    for(int i = 25 ; ~ i ; -- i) if(deep[par[u][i]] >= deep[v]) u = par[u][i];
    if(u == v) return u;
    for(int i = 25 ; ~ i ; -- i) if(par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    return par[u][0];
}

ll f[N], g[N][2], ans1, ans2, sz[N];

void dfs(int u) {
    sz[u] = vis[u], f[u] = 0, g[u][0] = 0x3f3f3f3f3f3f3f3fll, g[u][1] = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        dfs(v);
        ll d = deep[v] - deep[u];
        f[u] += f[v] + sz[v] * (k - sz[v]) * d;
        ans1 = min(ans1, g[u][0] + g[v][0] + d);
        ans2 = max(ans2, g[u][1] + g[v][1] + d);
        g[u][0] = min(g[u][0], g[v][0] + d);
        g[u][1] = max(g[u][1], g[v][1] + d);
        sz[u] += sz[v];
    }
    if(vis[u]) {
        ans1 = min(ans1, g[u][0]);
        ans2 = max(ans2, g[u][1]);
        g[u][0] = 0;
    }
    head[u] = vis[u] = 0;
}

void sol() {
    ans1 = 0x3f3f3f3f3f3f3f3fll, ans2 = 0;
    tot = top = 0;
    scanf("%d", &k);
    for(int i = 1 ; i <= k ; ++ i) scanf("%d", &bak[i]);
    sort(bak + 1, bak + 1 + k, cmp);
    for(int i = 1 ; i <= k ; ++ i) {
        int u = bak[i];
        vis[u] = 1;
        if(top) {
            int lca = getlca(u, sta[top]);
            while(dfn[lca] < dfn[sta[top]]) {
                if(dfn[lca] >= dfn[sta[top - 1]]) {
                    add(lca, sta[top]);
                    if(lca != sta[-- top]) sta[++ top] = lca;
                    break;
                }
                add(sta[top - 1], sta[top]), -- top;
            }
        }
        sta[++ top] = u;
    }
    while(top > 1) add(sta[top - 1], sta[top]), -- top;
    dfs(sta[1]);
    printf("%lld %lld %lld\n", f[sta[1]], ans1, ans2);
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) scanf("%d%d", &u, &v), add(u, v), add(v, u);
    dfs(1, 0);
    memset(head, 0, sizeof head), tot = dfn[0] = 0;
    scanf("%d", &q);
    while(q --) {
        sol();
    }
}
