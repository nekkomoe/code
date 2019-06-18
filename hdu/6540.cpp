#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

int n, m, k;
int mxh[5010], vis[5010];
ll f[5010][5010], g[5010];
vector<int> G[5010];

void dfs(int u, int fa) {
    for(int v: G[u]) {
        if(v != fa) {
            dfs(v, u);
            mxh[u] = max(mxh[u], mxh[v] + 1);
            memcpy(g, f[u], sizeof g);
            for(int i = 0 ; i <= min(k, mxh[u]) ; ++ i) {
                for(int j = 0 ; j <= min(k, mxh[v]) ; ++ j) {
                    if(i + j + 1 <= k) {
                        (g[max(i, j + 1)] += f[u][i] * f[v][j] % mod) %= mod;
                    }
                }
            }
            for(int i = 0 ; i <= mxh[u] ; ++ i) {
                f[u][i] = g[i];
            }
            for(int i = 0 ; i <= mxh[u] ; ++ i) {
                (f[u][i + 1] += f[v][i]) %= mod;
            }
        }
    }
    if(vis[u]) {
        f[u][0] = 1;
        for(int i = 1 ; i <= mxh[u] ; ++ i) {
            (f[u][i] *= 2) %= mod;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    for(int i = 1, x ; i <= m ; ++ i) {
        scanf("%d", &x);
        vis[x] = 1;
    }
    dfs(1, 0);
    ll ans = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        ans = (ans + f[1][i]) % mod;
    }
    printf("%lld\n", ans);
}
