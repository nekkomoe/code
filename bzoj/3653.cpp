%:pragma GCC optimize(2)
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int head[N], rest[N * 2], to[N * 2], tot, h[N], r[N], id[N], k[N], tmp, n, q;
inline void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }
ll ans[N], bit[N];
inline ll query(int x) { ll r = 0; for( ; x ; x -= x & -x) r += bit[x]; return r; }
int dfs(int u, int fa, int dep) {
    int sz = 1;
    for(int i = h[u] ; i ; i = r[i]) {
        ans[id[i]] += query(min(n, dep + k[i]));
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) sz += dfs(v, u, dep + 1);
    }
    for(int i = h[u] ; i ; i = r[i]) {
        ans[id[i]] = query(min(n, dep + k[i])) - ans[id[i]] + (ll) min(dep - 1, k[i]) * (sz - 1);
    }
    for(int i = dep ; i <= n ; i += i & -i) bit[i] += sz - 1;
    return sz;
}
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    for(int i = 1, p, k ; i <= q ; ++ i) {
        scanf("%d%d", &p, &k);
        id[++ tmp] = i, :: k[tmp] = k, r[tmp] = h[p], h[p] = tmp;
    }
    dfs(1, 0, 1);
    for(int i = 1 ; i <= q ; ++ i) printf("%lld\n", ans[i]);
}
