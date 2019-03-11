#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, mod = 998244353;

vector<int> g[N];

int n, q;

int fa[N][22], dep[N];

void dfs(int u) {
    dep[u] = dep[fa[u][0]] + 1;
    for(int i = 1 ; i <= 20 ; ++ i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for(int v: g[u]) {
        if(v != fa[u][0]) {
            fa[v][0] = u;
            dfs(v);
        }
    }
}

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

ll getdis(int i, int j) {
    // printf("dis %d, %d = %d, lca = %d\n", i, j, dep[i] + dep[j] - 2 * dep[getlca(i, j)], getlca(i, j));
    return dep[i] + dep[j] - 2 * dep[getlca(i, j)];
}

struct E {
    int u, v;
} e[N]; int a[N], rev[N];

ll s_dep_i_i[N]; // d[x] * x * x
ll s_dep_i[N]; // d[x] * x
ll s_dep[N]; // d[x]
ll S[N]; // i
ll s_dep_i_si_minus1[N]; // dep[x] * x * S[x - 1]
ll s_dep_si[N]; // dep[x] * S[x]
ll s_dep_i_si[N]; // dep[x] * x * S[x]

ll ans;

ll h[N];

namespace DFZ {

    int root, f[N], sz[N], size, ban[N], top[N];

    map<int, int> has[N];

    int getson(int u, int p) {
        // u -> p 的儿子
        if(u == p) return -1;
        int lcaup = getlca(u, p), res = 0;
        if(lcaup == u) {
            for(int i = 20 ; ~ i ; -- i) {
                if(dep[fa[p][i]] > dep[u]) {
                    p = fa[p][i];
                }
            }
            res = p;
            // printf("in way 1, res = %d\n", res);
        } else {
            res = fa[u][0];
        }
        if(has[u].find(res) == has[u].end()) return -1;
        return res;
    }

    void getrt(int u, int fa) {
        sz[u] = 1, f[u] = 0;
        for(int v: g[u]) {
            if(!ban[v] && v != fa) {
                getrt(v, u);
                sz[u] += sz[v];
                f[u] = max(f[u], sz[v]);
            }
        }
        f[u] = max(f[u], size - sz[u]);
        if(f[u] < f[root]) root = u;
    }

    void sol(int u) {
        ban[u] = 1;
        for(int v: g[u]) {
            if(!ban[v]) {
                root = 0, size = sz[v], getrt(v, u);
                top[root] = u;
                sol(root);
                has[u][v] = 1;
            }
        }
    }

    // id 以及 id*dis
    ll s_id[N];
    ll s_id_dis[N];
    map<int, ll> mp_s_id[N];
    map<int, ll> mp_s_id_dis[N];

    ll ask(int p) {
        ll res = 0;
        for(int u = p ; p ; p = top[p]) {
            int son = getson(p, u);
            ll sum_id = s_id[p], sum_id_dis = s_id_dis[p];
            if(son != -1) {
                (sum_id -= mp_s_id[p][son]) %= mod;
                (sum_id_dis -= mp_s_id_dis[p][son]) %= mod;
            }
            res = (res + sum_id_dis + sum_id * getdis(u, p) % mod) % mod;
        }
        return res;
    }

    void modify(int p) {
        for(int u = p ; p ; p = top[p]) {
            int son = getson(p, u);
            ll dis = getdis(u, p);

            // printf("u = %d, top = %d, son = %d\n", u, p, son);

            (s_id[p] += u) %= mod;
            (s_id_dis[p] += (ll) u * dis % mod) %= mod;
            if(son != -1) {
                (mp_s_id[p][son] += u) %= mod;
                (mp_s_id_dis[p][son] += (ll) u * dis % mod) %= mod;
            }
        }
    }

    void init() {
        f[0] = 0x3f3f3f3f;
        root = 0, size = n, getrt(1, 0), sol(root);
        // for(int i = 1 ; i <= n ; ++ i) {
        //     printf("tp[%d] = %d\n", i, top[i]);
        // }
    }
}

ll API_getans(int p) {
    // printf("ask %d, answer = %lld\n", p, DFZ :: ask(p));
    return DFZ :: ask(p);
}

void API_upd(int p) {
    // printf("upd %d\n", p);
    DFZ :: modify(p);
}

void initH() {

    API_upd(1);

    for(int k = 1 ; k < n ; ++ k) {
        ll val = 0;
        // for(int i = 1 ; i <= k ; ++ i) {
        //     (val += (ll) 2 * dep[getlca(k + 1, i)] * i % mod) %= mod;
        // }

        val = s_dep_i[k] + (ll) dep[k + 1] * S[k] % mod;

        val -= API_getans(k + 1);
        API_upd(k + 1);
        // for(int i = 1 ; i <= k ; ++ i) {
        //     (val -= (ll) getdis(i, k + 1) * i % mod) %= mod;
        // }

        h[k] = val;
    }
}

namespace DO_SUB_5 {
    ll f[N], g[N];
    void runprog() {
        g[1] = 2 * dep[1] % mod;

        for(int k = 1 ; k < n ; ++ k) {
            g[k + 1] = (g[k] + (ll) 2 * dep[k + 1] * (k + 1) % mod + h[k]) % mod;
        }

        for(int k = 1 ; k <= n ; ++ k) {
            f[k] = g[k] * (k + 1) % mod;
        }
    }
}

namespace DO_SUB_6 {
    ll f[N];
    void runprog() {
        f[1] = 2 * dep[1] % mod;

        for(int k = 1 ; k < n ; ++ k) {
            f[k + 1] = (f[k] + (ll) 2 * dep[k + 1] * (k + 1) % mod * (k + 1) % mod + (ll) (k + 1) * h[k] % mod) % mod;
        }
    }
}

void sol_parts(int k) {

    // for(int i = 1 ; i <= k ; ++ i) {
    //     for(int j = i ; j <= k ; ++ j) {
    //         ll x = (dep[i] + dep[j] - 2 * dep[getlca(i, j)]) % mod;
    //         ll y = (ll) i * (k - j + 1) % mod;
    //         (ans += x * y % mod) %= mod;
    //     }
    // }

    ll p = k + 1;
    // for(int i = 1 ; i <= k ; ++ i) {
    //     for(int j = i ; j <= k ; ++ j) {
    //         // ll x = (ll) dep[i] * i % mod * p % mod;
    //         ll x = 0;
    //         // ll y = (ll) -dep[i] * i % mod * j % mod;
    //         ll y = 0;
    //         // ll z = (ll) dep[j] * i % mod * p % mod;
    //         ll z = 0;
    //         // ll u = (ll) -dep[j] * i % mod * j % mod;
    //         ll u = 0;
    //         // ll v = (ll) -2 * dep[getlca(i, j)] * i % mod * p % mod;
    //         ll v = 0;
    //         // ll w = (ll) 2 * dep[getlca(i, j)] * i % mod * j % mod;
    //         ll w = 0;
    //         ans += (x + y + z + u + v + w) % mod;
    //     }
    // }

    // do part 1
    (ans += (p * p % mod * s_dep_i[k] % mod - p * s_dep_i_i[k] % mod) % mod) %= mod;

    // do part 2
    (ans -= S[k] * s_dep_i[k] % mod - s_dep_i_si_minus1[k]) %= mod;

    // do part 3
    (ans += p * s_dep_si[k] % mod) %= mod;

    // do part 4
    (ans -= s_dep_i_si[k]) %= mod;

    // do part 5
    (ans -= DO_SUB_5 :: f[k]) %= mod;

    // do part 6
    (ans += DO_SUB_6 :: f[k]) %= mod;
}

void runprog(int k) {
    ans = 0;

    // another good force
    sol_parts(k);

    // good force
    // for(int x = 1 ; x <= k ; ++ x) {
    //     for(int y = x ; y <= k ; ++ y) {
    //         ll val = (ll) x * (k - y + 1) % mod;
    //         (ans += getdis(x, y) * val % mod) %= mod;
    //     }
    // }

    // force
    // for(int i = 1 ; i <= k ; ++ i) {
    //     for(int j = i ; j <= k ; ++ j) {
    //         for(int x = i ; x <= j ; ++ x) {
    //             for(int y = x ; y <= j ; ++ y) {
    //                 // ans = (ans + getdis(x, y)) % mod;
    //                 ans = (ans + getdis(a[x], a[y])) % mod;
    //             }
    //         }
    //     }
    // }

    if(ans < 0) ans += mod;
    printf("%lld\n", ans);
}

int main() {
    // freopen("sumsumsumsum.in", "r", stdin);
    // freopen("sumsumsumsum.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1 ; i < n ; ++ i) {
        scanf("%d%d", &e[i].u, &e[i].v);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        rev[a[i]] = i;
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        u = rev[e[i].u], v = rev[e[i].v];
        // u = e[i].u, v = e[i].v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);

    for(int i = 1 ; i <= n ; ++ i) {
        s_dep_i_i[i] = (s_dep_i_i[i - 1] + (ll) dep[i] * i % mod * i % mod) % mod;
        s_dep_i[i] = (s_dep_i[i - 1] + (ll) dep[i] * i % mod) % mod;
        s_dep[i] = (s_dep[i - 1] + dep[i]) % mod;
        S[i] = (S[i - 1] + i) % mod;
        s_dep_i_si_minus1[i] = (s_dep_i_si_minus1[i - 1] + (ll) dep[i] * i % mod * S[i - 1] % mod) % mod;
        s_dep_si[i] = (s_dep_si[i - 1] + (ll) dep[i] * S[i] % mod) % mod;
        s_dep_i_si[i] = (s_dep_i_si[i - 1] + (ll) dep[i] * i % mod * S[i] % mod) % mod;
    }

    DFZ :: init();

    initH();
    DO_SUB_5 :: runprog();
    DO_SUB_6 :: runprog();

    for(int i = 1 ; i <= n ; ++ i) {
        runprog(i);
    }
}
