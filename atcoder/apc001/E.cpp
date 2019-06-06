#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, ans;
vector<int> g[N];
int vis[N];
int dfs(int u, int fa) {
    if(g[u].size() > 2) return u;
    else for(int v: g[u]) if(v != fa) return dfs(v, u);
    return u;
}
int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for(int i = 0 ; i < n ; ++ i) {
        if(g[i].size() == 1) {
            vis[dfs(i, -1)] = 1;
            ++ ans;
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        ans -= vis[i];
    }
    printf("%d\n", max(1, ans));
}
