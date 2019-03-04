#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 60, mod = 998244353;

int n, k;
vector<int> g[N];
ll f[N][N][2], h[N][2], C[N][N], sz[N], ans, t[N];

void upd(ll &tar, ll x) {
    tar = (tar + x) % mod;
}

ll pw(ll a, ll b) {
    if(b < 0) return pw(pw(a, -b), mod - 2);
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

void dfs(int u) {
    f[u][0][0] = f[u][0][1] = sz[u] = 1;
    for(int v: g[u]) {
        dfs(v);
        memset(h, 0, sizeof h);
        for(int i = 0 ; i < sz[u] ; ++ i) {
            for(int j = 0 ; j < sz[v] ; ++ j) {
                upd(h[i + j][0], f[u][i][0] * f[v][j][1]);
                upd(h[i + j][1], f[u][i][1] * f[v][j][1]);
                upd(h[i + j + 1][0], f[u][i][0] * f[v][j][0]);
                upd(h[i + j + 1][1], f[u][i][0] * f[v][j][1] % mod
                                   + f[u][i][1] * f[v][j][0] % mod);
            }
        }

        memcpy(f[u], h, sizeof h);
        sz[u] += sz[v];
    }
}

int main() {
    scanf("%d%d", &n, &k), k = min(k, n - 1);
    for(int i = 2, fa ; i <= n ; ++ i) {
        scanf("%d", &fa);
        g[fa + 1].push_back(i);
    }
    dfs(1);
    C[0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= i ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }

    for(int i = 0 ; i < n ; ++ i) {
        t[i] = f[1][i][1] * pw(n, n - i - 2) % mod;
    }
    for(int i = n - 1 ; i >= n - 1 - k ; -- i) {
        for(int j = i + 1 ; j <= n - 1 ; ++ j) {
            t[i] = (t[i] - t[j] * C[j][i] % mod) % mod;
        }
        ans = (ans + t[i]) % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
