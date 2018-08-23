#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e7 + 10, mod = 1e9 + 7;
int fa[N], x[N], y[N], n, m, sz[N];
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
int cnt[N], vis[N], deg[N], g[N];
ll fac[N];
ll ans;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}
ll sol(int s) {
    ll res = 0;
    int flag = 0, k = 0, sum = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        if((s >> (i - 1)) & 1) {
            int u = x[i], v = y[i];
            fa[u] = u, fa[v] = v;
            vis[u] = 0, vis[v] = 0;
            deg[u] = 0, deg[v] = 0;
            g[u] = 0, g[v] = 0;
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if((s >> (i - 1)) & 1) {
            int u = x[i], v = y[i];
            if(deg[u] == 0) ++ sum;
            if(deg[v] == 0) ++ sum;
            if((++ deg[u]) >= 3 || (++ deg[v]) >= 3) return 0;
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if((s >> (i - 1)) & 1) {
            int u = get(x[i]), v = get(y[i]);
            if(u == v) flag = 1;
            fa[u] = v;
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if((s >> (i - 1)) & 1) {
            int u = get(x[i]);
            if(!g[u]) {
                g[u] = 1;
                ++ k;
            }
        }
    }
    if(flag && (cnt[s] != n || k > 1)) {
        return 0;
    }
    res = fac[n - sum + k - 1] * pw(2, k) % mod * pw(2, mod - 2) % mod;
    if(cnt[s] & 1) res = -res;
    return res;
}

int main() {
    freopen("lighthouse.in", "r", stdin);
    freopen("lighthouse.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i < (1 << m) ; ++ i) cnt[i] = cnt[i >> 1] + (i & 1);
    for(int i = fac[0] = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    for(int i = 1 ; i <= m ; ++ i) scanf("%d%d", &x[i], &y[i]);
    for(int s = 0 ; s < (1 << m) ; ++ s) {
        ll t = sol(s);
        ans = (ans + t) % mod;
    }
    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
}
