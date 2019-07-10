#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define NEKKODEBUG

#ifdef NEKKODEBUG
#define printf
#define puts
#endif

int main() {

    // ---------------------------------------DECLARE--------------------------------------
    const int mod = 998244353;

    auto pw = [&] (ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod) {
            if(b & 1) {
                r = r * a % mod;
            }
        }
        return r;
    };

    auto getinv = [&] (ll n) {
        return pw(n, mod - 2);
    };

    auto upd = [&] (ll &a, ll b) {
        a = (a + b) % mod;
    };

    auto get_fac_invfac = [&] (int n) {
        vector<int> fac(n + 5), invfac(n + 5);
        fac[0] = invfac[0] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            fac[i] = (ll) fac[i - 1] * i % mod;
        }
        invfac[n] = getinv(fac[n]);
        for(int i = n - 1 ; i >= 1 ; -- i) {
            invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
        }
        return make_pair(fac, invfac);
    };

    auto C = [&] (int n, int m) {
        const int MXN = 1e5;
        static vector<int> fac, invfac;
        static int flag = ([&] () {
            auto tmp = get_fac_invfac(MXN + 5);
            fac = tmp.first, invfac = tmp.second;
            return 0;
        }) ();
        return n < m || m < 0 ? 0 : (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    };

    // ----------------------------------------BEGIN---------------------------------------
    
    struct Graph {
        int n;
        vector<vector<int> > g;
        vector<int> val;
        vector<tuple<int, int> > res_eds;
        void readtree(int _n, int m) {
            n = _n;
            vector<tuple<int, int, int> > eds;
            for(int i = 1 ; i <= m ; ++ i) {
                int u, v, w; scanf("%d%d%d", &u, &v, &w);
                eds.emplace_back(w, u, v);
            }
            sort(eds.begin(), eds.end());

            vector<int> fa(4 * n + 5);
            val.resize(4 * n + 5);
            g.resize(4 * n + 5);
            // 实际上两倍空间就够了，因为kruskal重构树本身就是三度化的树……
            for(int i = 1 ; i < fa.size() ; ++ i) {
                fa[i] = i;
            }
            function<int(int)> get = [&] (int u) {
                return u == fa[u] ? u : fa[u] = get(fa[u]);
            };
            for(auto e: eds) {
                int w, u, v; tie(w, u, v) = e;
                u = get(u), v = get(v);
                if(u != v) {
                    val[fa[u] = fa[v] = ++ n] = w;
                    auto lk = [&] (int u, int v) {
                        g[u].emplace_back(v);
                        g[v].emplace_back(u);
                    };
                    lk(n, u), lk(n, v);
                    res_eds.emplace_back(n, u);
                    res_eds.emplace_back(n, v);
                }
            }
        }
    } A, B;

    int n, m; scanf("%d%d", &n, &m);
    A.readtree(n, m), B.readtree(n, m);
    int bakn = n;
    
    // 对A进行边分治，在第二棵树上枚举

    n = A.n;
    vector<int> head(n + 5), rest(2 * n + 5), to(2 * n + 5);

    int tot = 1;
    for(auto e: A.res_eds) {
        int u, v; tie(u, v) = e;
        auto add = [&] (int u, int v) {
            to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
        };
        add(u, v), add(v, u);
        // printf("lk %d, %d\n", u, v);
    }

    vector<int> ban(2 * n + 5); // 边分治的ban掉的边
    vector<vector<int> > ch(30 * n + 5, vector<int> (2)); // 边分树上每个节点
    vector<int> hd(n + 5); // 边分树每个点的根
    vector<int> dn(n + 5); // 边分树每个点的最底端
    vector<int> tval(30 * n + 5); // 边分树每个点的权值
    vector<int> tsz(30 * n + 5); // 边分树每个点的子树大小
    vector<int> edup(n + 5); // 每个点从哪条边来的
    vector<int> tag(n + 5); // 分治中心的时候记录一下上面的点

    // printf("%d %d\n", tot, ban.size());
    // return 0;

    int spl_cnt = 0;
    ([&] () {
        // 跑边分治
        vector<int> sz(n + 5);
        int size, root, mxrot;
        vector<int> dep(n + 5), tfa(n + 5);

        for(int i = 1 ; i <= n ; ++ i) {
            hd[i] = ++ spl_cnt;
            dn[i] = hd[i];
        }

        ([&] () {
            function<void(int, int)> dfs = [&] (int u, int fa) {
                tfa[u] = fa;
                dep[u] = dep[fa] + 1;
                // printf("%d %d %d\n", u, fa, dep[u]);
                for(int i = head[u] ; i ; i = rest[i]) {
                    int v = to[i];
                    if(v != fa) {
                        dfs(v, u);
                        edup[v] = i;
                    }
                }
            };
            // 有根树
            dfs(n, 0);
        }) ();

        // exit(0);

        // for(int i = 1 ; i <= n ; ++ i) {
        //     printf("dep[%d] = %d\n", i, dep[i]);
        // }

        function<void(int, int)> getsz = [&] (int u, int fa) {
            // printf("%d, %d, %d\n", u, fa, dep[u]);
            sz[u] = 1;
            for(int i = head[u] ; i ; i = rest[i]) {
                int v = to[i];
                if(!ban[i] && v != fa) {
                    getsz(v, u);
                    sz[u] += sz[v];
                    int val = max(sz[v], size - sz[v]);
                    if(val <= mxrot) {
                        mxrot = val;
                        root = i;
                    }
                }
            }
        };

        function<void(int)> sol = [&] (int e) {
            if(!e) {
                return ;
            }


            // int deg = 0;
            // for(int i = head[to[e]] ; i ; i = rest[i]) {
            //     ++ deg;
            // }
            // printf("deg = %d, vis in edges (%d, %d), %d\n", deg, to[e], to[e ^ 1], dp);

            ban[e] = ban[e ^ 1] = 1;

            int u = to[e], v = to[e ^ 1];
            if(dep[u] > dep[v]) {
                swap(u, v);
            }

            ([&] (int x) {
                function<void(int, int, int)> dfs = [&] (int u, int fa, int mxval) {
                    // printf("tag vis %d\n", u);

                    if(tag[u]) {
                        mxval = A.val[u];
                    }

                    ([&] (int x) {
                        ch[dn[x]][0] = ++ spl_cnt;
                        dn[x] = ch[dn[x]][0];
                        if(x <= bakn) {
                            tsz[spl_cnt] = 1;
                            tval[spl_cnt] = mxval;
                        }
                    }) (u);

                    for(int i = head[u] ; i ; i = rest[i]) {
                        int v = to[i];
                        if(!ban[i] && v != fa) {
                            dfs(v, u, mxval);
                        }
                    }
                };
                dfs(x, 0, 0);
            }) (([&] (int x, int vls) {
                while(x) {
                    tag[x] = vls;
                    if(!tfa[x] || ban[edup[x]]) {
                        return x;
                    }
                    x = tfa[x];
                }
                assert(0);
                return -1;
            }) (u, 1));


            ([&] (int x, int vls) {
                while(x) {
                    tag[x] = vls;
                    if(!tfa[x] || ban[edup[x]]) {
                        break;
                    }
                    x = tfa[x];
                }
            }) (u, 0);
            
            ([&] (int x) {
                function<void(int, int)> dfs = [&] (int u, int fa) {

                    ([&] (int x) {
                        ch[dn[x]][1] = ++ spl_cnt;
                        dn[x] = ch[dn[x]][1];
                        if(x <= bakn) {
                            tsz[spl_cnt] = 1;
                        }
                    }) (u);

                    for(int i = head[u] ; i ; i = rest[i]) {
                        int v = to[i];
                        if(!ban[i] && v != fa) {
                            dfs(v, u);
                        }
                    }
                };
                dfs(x, 0);
            }) (v);

            vector<tuple<int, int> > nxt;
            nxt.emplace_back(to[e], sz[to[e]]);
            nxt.emplace_back(to[e ^ 1], size - sz[to[e]]);
            for(auto nt: nxt) {
                int v; tie(v, size) = nt;
                mxrot = 0x3f3f3f3f, root = 0;
                getsz(v, 0), sol(root);
            }
        };

        mxrot = 0x3f3f3f3f, root = 0, size = n;
        getsz(1, 0);
        // return 0;
        sol(root);
    }) ();

    // return 0;

    // 建完边分树了，开始合并它

    for(int i = 1 ; i <= n ; ++ i) {
        printf("hd[%d] = %d\n", i, hd[i]);
        function<void(int)> dfs = [&] (int u) {
            for(int i = 0 ; i < 2 ; ++ i) {
                int v = ch[u][i];
                if(v) {
                    printf("%d -> %d(%d)(val = %d, sz = %d)\n", u, v, i, tval[v], tsz[v]);
                    dfs(v);
                }
            }
        };
        dfs(hd[i]);
        puts("");
    }

    ([&] () {
        ll ans = 0;
        auto g = B.g;
        function<void(int, int) > dfs = [&] (int u, int fa) {
            ll coef = 0;
            function<int(int, int)> merge = [&] (int x, int y) {
                if(!x || !y) {
                    return x | y;
                }
                printf("%d * %d, %d * %d\n", tval[ch[x][0]], tsz[ch[y][1]], tval[ch[y][0]], tsz[ch[x][1]]);
                (coef += (ll) tval[ch[x][0]] * tsz[ch[y][1]] % mod) %= mod;
                (coef += (ll) tval[ch[y][0]] * tsz[ch[x][1]] % mod) %= mod;
                (tval[x] += tval[y]) %= mod;
                tsz[x] += tsz[y];
                ch[x][0] = merge(ch[x][0], ch[y][0]);
                ch[x][1] = merge(ch[x][1], ch[y][1]);
                return x;
            };
            for(int v: g[u]) {
                if(v != fa) {
                    // printf("tree 2 %d(%d) -> %d\n", u, B.val[u], v);
                    dfs(v, u);
                    coef = 0;
                    hd[u] = merge(hd[u], hd[v]);
                    printf("merge %d(%d) -> %d, ex coef = %lld\n", u, B.val[u], v, coef);
                    ans = (ans + (ll) coef * B.val[u] % mod) % mod;
                }
            }
        };
        dfs(B.n, 0);
        #undef printf
        printf("%lld\n", (ans % mod + mod) % mod);
    }) ();
    
    // -----------------------------------------END----------------------------------------

    return 0;
}
