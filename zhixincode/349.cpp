#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10;

int n, a[N]; vector<int> g[N];

int dep[N], f[N];

void dfs(int u, int fa) {
    if(a[u]) f[dep[u]] ++;
    for(int v: g[u]) {
        if(v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for(int i = n ; ~ i ; -- i) {
        f[i] += f[i + 1];
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i]) {
            ans = max(ans, dep[i] + f[dep[i]]);
        }
    }
    printf("%d\n", ans - 1);
}
