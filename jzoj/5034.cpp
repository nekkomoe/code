#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 100, mod = 998244353;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, k;

vector<int> g[N];

ll fac[N], invfac[N];
ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

ll calc(ll S, ll n, ll prod) {
    return pw(S, n - 2) % mod * prod % mod;
}

vector<pair<int, int> > tar;

namespace dbs {

    vector<pair<int, int> > ed;
    int acc[N]; int get(int x) { return x == acc[x] ? x : acc[x] = get(acc[x]); }
    int cnt[int(1e5)], ans;
    map<pair<int, int>, bool> vis;

    void sol(int s) {
        int res = 0;
        for(int i = 1 ; i <= n ; ++ i) acc[i] = i;
        for(int i = 0 ; i < ed.size() ; ++ i) {
            if(s & (1 << i)) {
                int u = ed[i].first, v = ed[i].second;
                if(get(u) == get(v)) {
                    return ;
                }
                acc[get(u)] = get(v);
                if(!vis.count(make_pair(min(u, v), max(u, v)))) {
                    ++ res;
                    if(res > k) {
                        return ;
                    }
                }
            }
        }
        ++ ans;
    }

    void runprog() {
        for(pair<int, int> t: tar) {
            vis[t] = 1;
            // printf("insert (%d, %d)\n", t.first, t.second);
        }

        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = i + 1 ; j <= n ; ++ j) {
                ed.push_back(make_pair(i, j));
                // printf("insert %d, %d\n", i, j);
            }
        }
        for(int s = 0 ; s < (1 << ed.size()) ; ++ s) {
            cnt[s] = cnt[s >> 1] + (s & 1);
        }
        for(int s = 0 ; s < (1 << ed.size()) ; ++ s) {
            if(cnt[s] != n - 1) continue;
            // puts("sol");
            sol(s);
        }
        printf("%d\n", ans);
    }
}

vector<int> jzsdl;
namespace sdctrdsdzf {

    int fa[N];
    ll y[N]; // (x, y)
    ll a[N][N];

    ll getdet(int n) {
        ll flag = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            int id = i;
            for(int j = i ; j <= n ; ++ j) {
                if(a[j][i]) {
                    id = j;
                    break;
                }
            }
            if(i != id) {
                for(int j = i ; j <= n ; ++ j) {
                    swap(a[i][j], a[id][j]);
                } flag ^= 1;
            }
            for(int j = i + 1 ; j <= n ; ++ j) {
                ll prod = pw(a[i][i], mod - 2) * a[j][i] % mod;
                for(int k = i ; k <= n ; ++ k) {
                    (a[j][k] -= prod * a[i][k] % mod) %= mod;
                }
            }
        }
        ll res = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            res = res * a[i][i] % mod;
        }
        res = flag ? -res : res;

        return (res % mod + mod) % mod;
    }

    ll sol(int x) {
        memset(a, 0, sizeof a);
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j < i ; ++ j) {
                if(i == fa[j] || j == fa[i]) {
                    a[i][j] = a[j][i] = -1;
                    ++ a[i][i];
                    ++ a[j][j];
                } else {
                    a[i][j] = a[j][i] = -x;
                    a[i][i] += x;
                    a[j][j] += x;
                }
            }
        }

        // for(int i = 1 ; i <= n ; ++ i) {
        //     for(int j = 1 ; j <= n ; ++ j) {
        //         a[i][j] = (a[i][j] % mod + mod) % mod;
        //         printf("%lld ", a[i][j]);
        //     }
        //     puts("");
        // }

        return getdet(n - 1);
    }

    ll f[N];
    ll lg[N];

    void lglrcz() {
        for(int i = 1 ; i <= n ; ++ i) {
            ll t = y[i];
            for(int k = 0 ; k < n ; ++ k) lg[k] = 0;
            lg[0] = 1;
            for(int j = 1 ; j <= n ; ++ j) {
                if(i == j) continue;
                t = t * pw(i - j, mod - 2) % mod;
                for(int k = n - 1 ; k >= 0 ; -- k) {
                    if(k) {
                        lg[k] = (lg[k] * -j % mod + lg[k - 1]) % mod;
                    } else {
                        lg[k] = lg[k] * -j % mod;
                    }
                }
            }
            for(int k = 0 ; k < n ; ++ k) {
                (f[k] += (ll) lg[k] * t % mod) %= mod;
            }
        }
    }

    void runprog() {
        for(int i = 2 ; i <= n ; ++ i) {
            fa[i] = jzsdl[i - 2];
        }
        for(int i = 1 ; i <= n ; ++ i) {
            y[i] = sol(i);
        }
        lglrcz();

        // for(int i = 1 ; i <= n ; ++ i) {
        //     printf("y[%d] = %lld\n", i, y[i]);
        // }

        ll ans = 0;
        for(int i = 0 ; i <= k ; ++ i) {
            ans = (ans + f[i]) % mod;
        }

        printf("%lld\n", (ans % mod + mod) % mod);
    }
}

int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d%d", &n, &k);
    init(n);
    for(int i = 2 ; i <= n ; ++ i) {
        int fa; scanf("%d", &fa); ++ fa;
        g[fa].push_back(i);

        tar.push_back(make_pair(min(fa, i), max(fa, i)));

        jzsdl.push_back(fa);
    }


    #ifndef ONLINE_JUDGE
    sdctrdsdzf :: runprog();
    #else


    if(k == 0 || n == 1) {
        puts("1");
    } else if(n <= 5) {
        dbs :: runprog();
    } else {
        sdctrdsdzf :: runprog();
    }

    #endif

}
