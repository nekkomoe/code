#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
typedef long long ll;

vector<int> g[N], fod[N], h[N];
int n, rt, deg[N], sz[N], fa[N][21], dep[N];

int getlca(int u, int v) {
    if(dep[u] < dep[v]) {
        swap(u, v);
    }
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) {
        return u;
    }
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

void dfs(int u) {
    sz[u] = 1;
    // for(int v: h[u]) {
    for(int a = 0 ; a < h[u].size() ; ++ a) {
        int v = h[u][a];
        dfs(v);
        sz[u] += sz[v];
    }
}

vector<pair<ll, ll> > e[N];
int vis[N];
ll dis[N];

int main() { int m;
    scanf("%d%d%d", &n, &m, &rt);
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    memset(dis, 0x3f, sizeof dis);

    priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > pq;
    pq.emplace(dis[rt] = 0, rt);
    while(pq.size()) {
        int u = pq.top().second; pq.pop();
        vis[u] = 1;
        for(auto ed: e[u]) {
            int v = ed.first, w = ed.second;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if(!vis[v]) {
                    pq.emplace(dis[v], v);
                }
            }
        }
    }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("dis[%d] = %lld\n", i, dis[i]);
    // }

    for(int u = 1 ; u <= n ; ++ u) {
        for(auto ed: e[u]) {
            int v = ed.first, w = ed.second;
            if(dis[v] == dis[u] + w) {
                // printf("%d -> %d\n", u, v);
                g[u].push_back(v);
                ++ deg[v];
                fod[v].push_back(u);
            }
        }
    }

    queue<int> q; q.push(rt);
    dep[rt] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        // for(int v: g[u]) {
        for(int b = 0 ; b < g[u].size() ; ++ b) {
            int v = g[u][b];
            if(!-- deg[v]) {
                q.push(v);
                int lca = u;
                // for(int w: fod[v]) {
                for(int a = 0 ; a < fod[v].size() ; ++ a) {
                    int w = fod[v][a];
                    lca = getlca(lca, w);
                }
                h[lca].push_back(v);
                dep[v] = dep[lca] + 1;
                fa[v][0] = lca;
                for(int i = 1 ; i <= 20 ; ++ i) {
                    fa[v][i] = fa[fa[v][i - 1]][i - 1];
                }
            }
        }
    }
    dfs(rt);
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(rt != i) {
            ans = max(ans, sz[i]);
        }
    }
    printf("%d\n", ans);
}
