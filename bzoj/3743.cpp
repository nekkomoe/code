#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10;
typedef long long ll;
int head[N], rest[N * 2], to[N * 2], w[N * 2], tot;
int que[N], n, k, tag[N], fa[N], sz[N], son[N], dis[N];
ll f[N][2], g[N][2], h[N][2];
void add(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }
    for(int i = 1, x ; i <= k ; ++ i) {
        scanf("%d", &x);
        tag[x] = 1;
    }
    int l, r;
    que[l = r = 1] = 1;
    while(l <= r) {
        int u = que[l ++];
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v != fa[u]) {
                dis[v] = w[i];
                fa[v] = u;
                que[++ r] = v;
            }
        }
    }
    for(int p = n ; p ; -- p) {
        int u = que[p];
        sz[u] = tag[u];
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v != fa[u] && sz[v]) {
                sz[u] += sz[v];
                f[u][0] += f[v][0] + 2ll * w[i];
                ll t = g[v][0] - w[i];
                if(t < g[u][0]) g[u][1] = g[u][0], g[u][0] = t, son[u] = v;
                else g[u][1] = min(g[u][1], t);
            }
        }
        f[u][1] = f[u][0] + g[u][0];
    }
    for(int p = 2 ; p <= n ; ++ p) {
        int u = que[p];
        if(sz[1] > sz[u]) {
            h[u][0] = h[fa[u]][0] + f[fa[u]][0] - f[u][0];
            h[u][1] = h[fa[u]][1] + f[fa[u]][0];
            if(son[fa[u]] == u) h[u][1] = min(h[u][1], h[fa[u]][0] + f[fa[u]][0] + g[fa[u]][1]);
            else h[u][1] = min(h[u][1], h[fa[u]][0] + f[fa[u]][1]);
            h[u][1] -= f[u][0] + dis[u];
            if(!sz[u]) {
                h[u][0] += 2ll * dis[u];
                h[u][1] += 2ll * dis[u];
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld\n", min(f[i][0] + h[i][1], f[i][1] + h[i][0]));
    }
}
