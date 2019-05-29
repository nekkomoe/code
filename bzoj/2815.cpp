#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

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

int main() {
    scanf("%d", &n), rt = n + 1;
    for(int u = 1, v ; u <= n ; ++ u) {
        while(1) {
            scanf("%d", &v);
            if(!v) {
                break;
            } else {
                g[v].push_back(u);
                fod[u].push_back(v);
                ++ deg[u];
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(!deg[i]) {
            deg[i] ++;
            g[rt].push_back(i);
            fod[i].push_back(rt);
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
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", sz[i] - 1);
    }
}
