#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, mod = 1e9 + 7, K = 210;

vector<int> to[N];

int n, k, sz[N];
ll f[N][K], g[K], S[K][K], fac[N], ans[N], output;

void dfs(int u, int fa) {
    sz[u] = f[u][0] = 1;
    for(int v: to[u]) {
        if(v == fa) continue;
        dfs(v, u);
        for(int i = 0 ; i <= k ; ++ i) g[i] = f[u][i];
        for(int j = 0 ; j <= min(k, sz[v]) ; ++ j) {
            (f[u][j] += f[v][j]) %= mod;
            if(j >= 1) (f[u][j] += f[v][j - 1]) %= mod;
        }
        for(int a = 0 ; a <= min(k, sz[u]) ; ++ a) {
            for(int b = 0 ; b <= min(k - a, sz[v]) ; ++ b) {
                ll val = g[a] * f[v][b] % mod;

                (f[u][a + b] += val) %= mod;
                (ans[a + b] += val) %= mod;

                (f[u][a + b + 1] += val) %= mod;
                (ans[a + b + 1] += val) %= mod;
            }
        }
        sz[u] += sz[v];
    }
}

int main() {
    scanf("%d%d", &n, &k);
    S[0][0] = 1, fac[0] = 1;
    for(int i = 1 ; i <= k ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
        for(int j = 1 ; j <= i ; ++ j) {
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % mod;
        }
    }
    for(int i = 1 ; i < n ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        to[u].push_back(v);
        to[v].push_back(u);
    }
    dfs(1, 0);
    for(int i = 1 ; i <= k ; ++ i) {
        output = (output + S[k][i] * ans[i] % mod * fac[i] % mod) % mod;
    }
    printf("%lld\n", (output % mod + mod) % mod);
}
