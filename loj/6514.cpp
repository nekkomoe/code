#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    // ---------------------------------------DECLARE--------------------------------------
    const int mod = 1e9 + 7;

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

    struct FastIO {
        #define S int(1e7)
        int wpos;
        char wbuf[S];
        FastIO() : wpos(0) {}
        inline int xchar() {
            static char buf[S];
            static int len = 0, pos = 0;
            if (pos == len)
                pos = 0, len = fread(buf, 1, S, stdin);
            if (pos == len) exit(0);
            return buf[pos++];
        }
        inline int operator () () {
            int c = xchar(), x = 0;
            while (c <= 32) c = xchar();
            for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
            return x;
        }
        inline ll operator ! () {
            int c = xchar(); ll x = 0;
            while (c <= 32) c = xchar();
            for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
            return x;
        }
        inline void wchar(int x) {
            if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
            wbuf[wpos++] = x;
        }
        inline void operator () (ll x) {
            if (x < 0) wchar('-'), x = -x;
            char s[24];
            int n = 0;
            while (x || !n) s[n++] = '0' + x % 10, x /= 10;
            while (n--) wchar(s[n]);
            wchar('\n');
        }
        inline void space(ll x) {
            if (x < 0) wchar('-'), x = -x;
            char s[24];
            int n = 0;
            while (x || !n) s[n++] = '0' + x % 10, x /= 10;
            while (n--) wchar(s[n]);
            wchar(' ');
        }
        inline void nextline() {
            wchar('\n');
        }
        ~FastIO()
        {
            if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
        }
        #undef S
    } io;

    // ----------------------------------------BEGIN---------------------------------------
    
    int n = io(), q = io(), clk = 0;
    static vector<vector<int> > g(n + 5), fa(20, vector<int> (n + 5)), ids(20, vector<int> (2 * n + 5)), vt(n + 10);
    static vector<int> dep(n + 5), dfn(n + 5), dfn_end(n + 5), sz(n + 5), lg(2 * n + 5), ban(n + 10);
    for(int i = 1, u, v ; i < n ; ++ i) {
        u = io(), v = io();
        g[u].emplace_back(v), g[v].emplace_back(u);
    }

    static auto merge = [&] (int u, int v) {
        return dep[u] < dep[v] ? u : v;
    };

    function<void(int)> dfs = [&] (int u) {
        ids[0][dfn[u] = ++ clk] = u;
        dep[u] = dep[fa[0][u]] + 1;
        for(int i = 1 ; i <= 19 ; ++ i) {
            fa[i][u] = fa[i - 1][fa[i - 1][u]];
        }
        sz[u] = 1;
        for(int v: g[u]) {
            if(v != fa[0][u]) {
                fa[0][v] = u;
                dfs(v);
                sz[u] += sz[v];
                ids[0][++ clk] = u;
            }
        }
        dfn_end[u] = clk;
    };
    dfs(1);
    lg[0] = -1;
    for(int i = 1 ; i <= clk ; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(int j = 1 ; j <= 19 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= clk ; ++ i) {
            ids[j][i] = merge(ids[j - 1][i], ids[j - 1][i + (1 << (j - 1))]);
        }
    }

    auto getlca = [&] (int u, int v) {
        int l = dfn[u], r = dfn[v];
        if(l > r) {
            swap(l, r);
        }
        int k = lg[r - l + 1];
        return merge(ids[k][l], ids[k][r - (1 << k) + 1]);
    };

    while(q --) {
        int k = io();
        vector<int> a;
        while(k --) {
            int x = io();
            a.emplace_back(x);
        }
        if(a.size() == 1) {
            io(n);
        } else {
            int u = a[0];
            vector<int> nds;
            nds.emplace_back(u);
            for(int i = 1 ; i < a.size() ; ++ i) {
                int v = a[i], lca = getlca(u, v);
                int dis = dep[u] + dep[v] - 2 * dep[lca], w;

                auto getloc = [&] (int u, int v, int lca, int dis) {
                    if(dep[u] - dep[lca] >= dis) {
                        for(int i = 19 ; ~ i ; -- i) {
                            if(dep[fa[i][u]] >= dep[lca]) {
                                int val = dep[u] - dep[fa[i][u]];
                                if(dis >= val) {
                                    dis -= val;
                                    u = fa[i][u];
                                }
                            }
                        }
                        return u;
                    } else {
                        dis = dep[u] + dep[v] - 2 * dep[lca] - dis;
                        for(int i = 19 ; ~ i ; -- i) {
                            if(dep[fa[i][v]] >= dep[lca]) {
                                int val = dep[v] - dep[fa[i][v]];
                                if(dis >= val) {
                                    dis -= val;
                                    v = fa[i][v];
                                }
                            }
                        }
                        return v;
                    }
                };

                ban[w = dis & 1 ? getloc(u, v, lca, (dis + 1) / 2) : getloc(u, v, lca, dis / 2 + 1)] = 1;
                nds.emplace_back(w);
            }

            ([&] () {
                sort(nds.begin(), nds.end(), [&] (int x, int y) {
                    return dfn[x] < dfn[y];
                });
                nds.erase(unique(nds.begin(), nds.end()), nds.end());
                for(int i = nds.size() - 1 ; i >= 1 ; -- i) {
                    nds.emplace_back(getlca(nds[i], nds[i - 1]));
                }
                sort(nds.begin(), nds.end(), [&] (int x, int y) {
                    return dfn[x] < dfn[y];
                });
                nds.erase(unique(nds.begin(), nds.end()), nds.end());
                stack<int> sta;

                for(int u: nds) {
                    while(sta.size() && dfn_end[sta.top()] < dfn[u]) {
                        sta.pop();
                    }
                    if(sta.size()) {
                        vt[sta.top()].emplace_back(u);
                        vt[u].emplace_back(sta.top());
                    }
                    sta.emplace(u);
                }
            }) ();

            auto get_first_son = [&] (int u, int anc) {
                for(int i = 19 ; ~ i ; -- i) {
                    if(dep[fa[i][u]] > dep[anc]) {
                        u = fa[i][u];
                    }
                }
                return u;
            };

            int ans = n;
            queue<int> q;
            for(int v: vt[u]) {
                q.emplace(v);
            }
            ban[u] = -1;
            while(q.size()) {
                int v = q.front(); q.pop();
                if(ban[v] == 0) {
                    ban[v] = -1;
                    for(int w: vt[v]) {
                        if(ban[w] != -1) {
                            q.emplace(w);
                        }
                    }
                } else {
                    ban[v] = -1;
                    int lca = getlca(u, v);
                    ans -= lca == v ? n - sz[get_first_son(u, lca)] : sz[v];
                }
            }
            io(ans);

            for(int u: nds) {
                vt[u].clear();
                ban[u] = 0;
            }
        }
    }
    
    // -----------------------------------------END----------------------------------------

    return 0;
}
