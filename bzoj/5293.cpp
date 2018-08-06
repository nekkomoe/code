#include <bits/stdc++.h>

using namespace std;

const int N = 6e5 + 10;

int head[N], rest[N], to[N], tot;

int n;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u] ,head[u] = tot;
}

typedef long long ll;

ll val[N][55];

const ll mod = 998244353;

int fa[N][30], dep[N];

void dfs(int u, int fa = 0, ll dep = 0) {
    :: fa[u][0] = fa;
    :: dep[u] = dep + 1;
    for(int i = 1 ; i <= 25 ; ++ i) :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    val[u][0] = 1;
    for(int i = 1 ; i <= 50 ; ++ i) val[u][i] = (val[u][i - 1] * dep) % mod;
    for(int i = 0 ; i <= 50 ; ++ i) val[u][i] = (val[u][i] + val[fa][i]) % mod;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u, dep + 1);
    }
}

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 25 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 25 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int m;

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1);
    scanf("%d", &m);
    for(int i = 1, u, v, k ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &k);
        int d = getlca(u, v);
        ll ans = val[u][k] + val[v][k] - val[d][k] - val[fa[d][0]][k];
        ans %= mod;
        ans += mod;
        ans %= mod;
        printf("%lld\n", ans);
    }
}
