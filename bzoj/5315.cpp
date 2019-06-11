#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 210;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, m;
ll ans;
int head[N], rest[N * N], to[N * N], tot = 1;
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int dfn[N], low[N], clk, sz[N];
int cut[N * N], esz[N * N];
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}
void dfs(int u, int fa) {
    dfn[u] = low[u] = ++ clk, sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        if(!dfn[v]) {
            dfs(v, u), sz[u] += sz[v];
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
        if(low[v] > dfn[u]) {
            // 割边
            cut[i] = cut[i ^ 1] = 1;
            upd(ans, (pw(2, sz[v]) - 1) * (pw(2, n - sz[v]) - 1) % mod);
            esz[i] = sz[v], esz[i ^ 1] = n - sz[v];
        }
    }
}

int vis[N];
int nxt(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!cut[i] && !vis[v]) {
            return v;
        }
    }
    return 0;
}
ll f[N][N][N], val[N];
void sol(int u) {
    int m = 0;
    for(int x = u ; x ; x = nxt(x)) {
        ++ m;
        vis[x] = 1;
        val[m] = 1;
        for(int i = head[x] ; i ; i = rest[i]) {
            int y = to[i];
            if(cut[i]) {
                val[m] += esz[i];
            }
        }
        val[m] = pw(2, val[m]) - 1;
    }
    if(m == 1) {
        return ;
    }
    memset(f, 0, sizeof f);
    for(int i = 1 ; i < m ; ++ i) {
        f[i][i][0] = val[i];
        for(int j = i + 1 ; j <= m ; ++ j) {
            for(int k = 0 ; k <= m ; ++ k) {
                if(j - k >= 0) {
                    for(int p = 0 ; p <= k ; ++ p) {
                        upd(f[i][j][k], f[i][j - k][p]);
                    }
                }
                for(int p = max(i, j - k + 1) ; p <= j - 1 ; ++ p) {
                    upd(f[i][j][k], f[i][p][k]);
                }
                (f[i][j][k] *= val[j]) %= mod;
            }
        }
        for(int j = i ; j <= m ; ++ j) {
            for(int k = 0 ; k <= m ; ++ k) {
                upd(ans, (m - max(k, m - (j - i))) * f[i][j][k] % mod);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    // 这图应该连通吧……
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i) {
        if(!vis[i]) {
            sol(i);
        }
    }
    printf("%lld\n", (ans * pw(pw(2, n), mod - 2) % mod + mod) % mod);
}
