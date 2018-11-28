#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 110, M = 1e4 + 10;

int n, m;

int from[M], to[M], w[M], tot;

int id[N], top[N], fa[N], cnt, root, dis[N];
ll ans;
const int inf = 0x3f3f3f3f;

int main() {
    scanf("%d%d%d", &n, &m, &root);
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        from[i] = u, to[i] = v, :: w[i] = w;
    }
    while(1) {
        for(int i = 1 ; i <= n ; ++ i) {
            id[i] = top[i] = 0, dis[i] = inf;
        }
        
        for(int i = 1 ; i <= m ; ++ i) {
            int u = from[i], v = to[i];
            if(u != v && w[i] < dis[v]) {
                dis[v] = w[i];
                fa[v] = u;
            }
        }
        
        int u; dis[root] = 0;
        
        for(int i = 1 ; i <= n ; ++ i) {
            if(dis[i] == inf) {
                return puts("-1"), 0;
            }
            ans += dis[i];
            for(u = i ; u != root && top[u] != i && id[u] == 0 ; u = fa[u]) {
                top[u] = i;
            }
            if(u != root && id[u] == 0) {
                id[u] = ++ cnt;
                for(int v = fa[u] ; v != u ; v = fa[v]) id[v] = cnt;
            }
        }
        if(cnt == 0) return printf("%lld\n", ans), 0;
        for(int i = 1 ; i <= n ; ++ i) {
            if(!id[i]) {
                id[i] = ++ cnt;
            }
        }
        for(int i = 1 ; i <= m ; ++ i) {
            int u = id[from[i]], v = id[to[i]], w = dis[to[i]];
            from[i] = u, to[i] = v;
            if(u != v)
                :: w[i] -= w;
        }
        n = cnt, root = id[root], cnt = 0;
    }
}

