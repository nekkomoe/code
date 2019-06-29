#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e4 + 10;
//const int N = 100;
int n;
vector<int> g[N];

bitset<N> f[N], h[N], pre[N], sub[N];
int vis[N];

void dfs(int u, int fa) {
    if(vis[u]) {
        f[u].set(0);
    }
    vector<int> tmp;
    for(int v: g[u]) {
        if(v != fa) {
            tmp.push_back(v);
            dfs(v, u);
            f[u] |= f[v] << 1;
        }
    }
    g[u] = tmp;
}

void go(int u) {
    if(vis[u]) {
        h[u].set(0);
    }
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        pre[i] = f[g[u][i]] << 1;
        if(i) {
            pre[i] |= pre[i - 1];
        }
    }
    for(int i = g[u].size() - 1 ; i >= 0 ; -- i) {
        sub[i] = f[g[u][i]] << 1;
        if(i != g[u].size() - 1) {
            sub[i] |= sub[i + 1];
        }
    }
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        h[v] = 0;
        if(i) {
            h[v] |= pre[i - 1] << 1;
        }
        if(i != g[u].size() - 1) {
            h[v] |= sub[i + 1] << 1;
        }
        h[v] |= h[u] << 1;
    }
    for(int v: g[u]) {
        go(v);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        if(x) {
            vis[i] = 1;
        }
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    go(1);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", int((f[i] | h[i]).count()));
    }
}
