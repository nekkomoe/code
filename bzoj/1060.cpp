#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int head[N], rest[N], to[N], w[N], tot;
void add(int u, int v, int w) { to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot; }
int n, m, root;
ll f[N], ans;
void dfs(int u, int fa) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            dfs(v, u);
            f[u] = max(f[u], f[v] + w[i]);
        }
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            ans += f[u] - f[v] - w[i];
        }
    }
}
int main() {
    scanf("%d%d", &n, &root);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }
    dfs(root, 0);
    printf("%lld\n", ans);
}
