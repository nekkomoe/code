#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10, K = 30;

const int mod = 1e9 + 7;

typedef long long ll;

ll c[K][K], fac[K], inv[K];

int n, k;

ll pw(ll a, ll b) {
    ll res = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) res = res * a % mod;
    return res;
}

void init() {
    fac[0] = 1;
    for(int i = 1 ; i <= k ; ++ i) fac[i] = fac[i - 1] * i % mod;
    inv[k] = pw(fac[k], mod - 2);
    for(int i = k ; i ; -- i) inv[i - 1] = inv[i] * i % mod;
    for(int i = 0 ; i <= k ; ++ i)
        for(int j = 0 ; j <= i ; ++ j)
            c[i][j] = fac[i] * inv[j] % mod * inv[i - j] % mod;
}

struct DXS {
    ll a[K];
    DXS() { memset(a, 0, sizeof a); }
    void init(int x) { fill(a, a + k + 1, x); }
} dxs_son[N], dxs_fa[N];

DXS operator + (DXS a, DXS b) {
    for(int i = 0 ; i <= k ; ++ i) a.a[i] = (a.a[i] + b.a[i]) % mod;
    return a;
}

DXS operator - (DXS a, DXS b) {
    for(int i = 0 ; i <= k ; ++ i) a.a[i] = (a.a[i] - b.a[i] + mod) % mod;
    return a;
}

DXS operator + (DXS a, ll b) {
    DXS res;
    b = (b + mod) % mod;
    ll pws[K];
    pws[0] = 1;
    for(int i = 1 ; i <= k ; ++ i) pws[i] = pws[i - 1] * b % mod;
    for(int i = k ; ~ i ; -- i)
        for(int j = i ; ~ j ; -- j)
            res.a[i] = (res.a[i] + a.a[j] * pws[i - j] % mod * c[i][j] % mod) % mod;
    return res;
}

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs1(int u, int fa) {
    dxs_son[u].init(1);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            dfs1(v, u);
            dxs_son[u] = dxs_son[u] + (dxs_son[v] + 1);
        }
    }
}

void dfs2(int u, int fa) {
    if(fa) dxs_fa[u] = (dxs_fa[fa] + 1) + ((dxs_son[fa] - (dxs_son[u] + 1)) + 1);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            dfs2(v, u);
        }
    }
}

void sol() {
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld\n", (dxs_fa[i] + dxs_son[i]).a[k]);
    }
    puts("");
}

int main() {
    while(scanf("%d%d", &n, &k) == 2) {
        memset(head, 0, sizeof head), tot = 0;
        init();
        for(int i = 1, u, v ; i < n ; ++ i) {
            scanf("%d%d", &u, &v);
            add(u, v), add(v, u);
        }
        dfs1(1, 0), dfs2(1, 0);
        sol();
    }
}

