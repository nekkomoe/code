#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, LEN = 500, mod = 1e9 + 7;

int n, m, q;
vector<int> G[N];

int k, a[N];

namespace force_min {

    // unordered_map<int, bool> tra[N];
    map<int, bool> tra[N];

    void init() {
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j: G[i]) {
                tra[i][j] = 1;
            }
        }
    }

    vector<int> g[N];

    ll f[N]; int deg[N];
    ll get_topo() {

        for(int i = 1 ; i <= k ; ++ i) {
            f[i] = 1;
            deg[i] = 0;
        }

        for(int i = 1 ; i <= k ; ++ i) {
            for(int j: g[i]) {
                ++ deg[j];
                // printf("deg[%d] ++ \n", j);
            }
        }

        queue<int> q;
        for(int i = 1 ; i <= k ; ++ i) {
            if(deg[i] == 0) {
                q.push(i);
                // printf("push %d\n", i);
            }
        }

        while(q.size()) {
            int u = q.front(); q.pop();
            // printf("u = %d\n", u);
            for(int v: g[u]) {
                if(!-- deg[v]) {
                    q.push(v);
                }
                (f[v] += f[u]) %= mod;
            }
        }

        ll res = 0;
        for(int i = 1 ; i <= k ; ++ i) {
            res = (res + f[i]) % mod;
        }
        res = (res - k) % mod;
        if(res < 0) res += mod;
        return res;
    }

    void runprog() {
        for(int i = 1 ; i <= k ; ++ i) {
            for(int j = 1 ; j <= k ; ++ j) {
                if(i != j) {
                    if(tra[a[i]].count(a[j])) {
                        g[i].push_back(j);
                        // printf("%d -> %d\n", i, j);
                    }
                }
            }
        }
        printf("%lld\n", get_topo());
        for(int i = 1 ; i <= k ; ++ i) {
            g[i].clear();
        }
    }
}

int bakdeg[N];

namespace force_max {

    ll f[N]; int deg[N], canvis[N];
    ll get_topo() {

        for(int i = 1 ; i <= n ; ++ i) {
            f[i] = canvis[i] = 0;
            deg[i] = bakdeg[i];
        }

        for(int i = 1 ; i <= k ; ++ i) {
            f[a[i]] = 1;
            canvis[a[i]] = 1;
        }

        queue<int> q;
        for(int i = 1 ; i <= n ; ++ i) {
            if(bakdeg[i] == 0) {
                q.push(i);
            }
        }

        while(q.size()) {
            int u = q.front(); q.pop();
            for(int v: G[u]) {
                if(!-- deg[v]) {
                    q.push(v);
                }
                if(canvis[v]) {
                    (f[v] += f[u]) %= mod;
                }
            }
        }

        ll res = 0;
        for(int i = 1 ; i <= k ; ++ i) {
            res = (res + f[a[i]]) % mod;
        }
        res = (res - k) % mod;
        if(res < 0) res += mod;
        return res;
    }

    void runprog() {
        printf("%lld\n", get_topo());
    }
}

int main() {
//    freopen("gondola.in", "r", stdin);
//    freopen("gondola.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
        ++ bakdeg[v];
    }
    force_min :: init();
    scanf("%d", &q);
    while(q --) {
        scanf("%d", &k);
        for(int i = 1 ; i <= k ; ++ i) {
            scanf("%d", &a[i]);
        }
        // force_max :: runprog(); continue;
        if(k <= LEN) {
            force_min :: runprog();
        } else {
            force_max :: runprog();
        }
    }
}
