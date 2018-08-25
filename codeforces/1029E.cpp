#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;

vector<int> g[N];

int n, fa[N], dis[N], vis[N], ans;

pair<int, int> f[N];

void dfs(int u) {
    f[u] = { dis[u], u };
    for(int v: g[u]) {
        if(v == fa[u]) continue;
        fa[v] = u;
        dis[v] = dis[u] + 1;
        dfs(v);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs(1);
    sort(f + 1, f + 1 + n);
    for(int i = n ; i ; -- i) {
        int dis = f[i].first, u = f[i].second;
        if(!vis[u] && u != 1 && dis > 2) {
            for(int v: g[fa[u]]) {
                vis[v] = 1;
            }
            vis[fa[u]] = 1;
            ++ ans;
        }
    }
    printf("%d\n", ans);
}
