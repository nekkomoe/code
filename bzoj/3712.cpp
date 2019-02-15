#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int N = 1e6 + 10;
 
int n, m, k;
 
int fa[N][22], lc[N], rc[N], dep[N];
 
int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
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
 
int g[N], cur[N], lca[N], a[N], b[N], id[N];
 
bool cmp(int a, int b) {
    return lca[a] == lca[b] ? a < b : lca[a] < lca[b];
}
 
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &g[i]);
        cur[i] = i;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        lc[fa[cur[u]][0] = n + i] = cur[u];
        rc[fa[cur[v]][0] = n + i] = cur[v];
        cur[v] = n + i;
    }
    dep[n + m + 1] = 1;
    for(int i = n + m ; i ; -- i) {
        if(!fa[i][0]) fa[i][0] = n + m + 1;
        dep[i] = dep[fa[i][0]] + 1;
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n + m + 1 ; ++ i) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
    for(int i = 1 ; i <= k ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        lca[i] = getlca(u, v);
        a[i] = u, b[i] = v;
        id[i] = i;
    }
    sort(id + 1, id + 1 + k, cmp);
    ll ans = 0;
    for(int i = 1 ; i <= k && lca[id[i]] <= n + m ; ++ i) {
        int x = id[i];
        ll mn = min(g[a[x]], g[b[x]]);
        g[a[x]] -= mn, g[b[x]] -= mn, ans += 2 * mn;
    }
    printf("%lld\n", ans);
}
