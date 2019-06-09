#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10, mod = 998244353, inv2 = (mod + 1) / 2;

int n;
vector<int> g[N];
ll ans, anpr = 1, f[N];

void dfs(int u, int fa) {
    ll &e = f[u] = 1;
    for(int v: g[u]) {
        if(v != fa) {
            dfs(v, u);
            e = e * (1 - (1 - f[v]) * inv2 % mod) % mod;
        }
    }
    e = 1 - e;
    ans = (ans + 2 * e) % mod;
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        anpr = anpr * 2 % mod;
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1, 0);
    printf("%lld\n", (ans * anpr % mod + mod) % mod);
}
