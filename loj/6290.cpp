#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 500010;

int n, m, T;

ll out[N];

namespace FenKuai {

    const int N = 100010;

    int f[320][320]; // f[i][j]: ?i???j????

    int cnt[N][320]; // cnt[i][j]: ??i??j???????

    int a[N], ans, sz, bel[N], l[N], r[N], tmp[N], len;

    void main() {
        len = (int) sqrt(n) + 1;
        for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
        for(int i = 1, t ; i <= n ; ++ i) {
            bel[i] = (i - 1) / len + 1;
            l[bel[i]] = l[bel[i]] ? l[bel[i]] : i;
            r[bel[i]] = i;
        }

        sz = bel[n];


        // init cnt
        for(int i = 1 ; i <= n ; ++ i) {
            ++ cnt[a[i]][bel[i]];
        }
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= sz ; ++ j) {
                cnt[i][j] += cnt[i][j - 1];
            }
        }

        // init f
        for(int i = 1 ; i <= bel[n] ; ++ i) {
            // ?????
            int lb = i, most = 0;
            for(int j = l[i] ; j <= n ; ++ j) {
                // ????
                int rb = bel[j];
                ++ tmp[a[j]];
                if(tmp[a[j]] > tmp[most] || (tmp[a[j]] == tmp[most] && a[j] < most)) {
                    most = a[j];
                }
                f[lb][rb] = most;
            }
            for(int j = l[i] ; j <= n ; ++ j) {
                tmp[a[j]] = 0;
            }
        }

        // sol
        for(int T = 1, ql, qr ; T <= m ; ++ T) {
            scanf("%d%d", &ql, &qr);

            // ????
            if(bel[ql] == bel[qr]) {
                // ??????,?brute force
                for(int i = ql ; i <= qr ; ++ i) {
                    ++ tmp[a[i]];
                    if(tmp[a[i]] > tmp[ans] || (tmp[a[i]] == tmp[ans] && a[i] < ans)) {
                        ans = a[i];
                    }
                }
                for(int i = ql ; i <= qr ; ++ i) {
                    tmp[a[i]] = 0;
                }
            } else {

                int bak = 0;
                // ???????????
                if(bel[ql] + 1 <= bel[qr] - 1) {
                    bak = ans = f[bel[ql] + 1][bel[qr] - 1];
                }

                // ???????????
                if(bel[ql] + 1 <= bel[qr] - 1) {
                    for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                        if(tmp[a[i]]) continue;
                        tmp[a[i]] = cnt[a[i]][bel[qr] - 1] - cnt[a[i]][bel[ql]];
                    }
                    for(int i = l[bel[qr]] ; i <= qr ; ++ i) {;
                        if(tmp[a[i]]) continue;
                        tmp[a[i]] = cnt[a[i]][bel[qr] - 1] - cnt[a[i]][bel[ql]];
                    }
                }
                for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                    ++ tmp[a[i]];
                }
                for(int i = l[bel[qr]] ; i <= qr ; ++ i) {
                    ++ tmp[a[i]];
                }
                if(bel[ql] + 1 <= bel[qr] - 1 && !tmp[ans]) {
                    tmp[ans] = cnt[ans][bel[qr] - 1] - cnt[ans][bel[ql]];
                }

                // ?????????
                for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                    if(tmp[a[i]] > tmp[ans] || (tmp[a[i]] == tmp[ans] && a[i] < ans)) {
                        ans = a[i];
                    }
                }
                for(int i = l[bel[qr]] ; i <= qr ; ++ i) {
                    if(tmp[a[i]] > tmp[ans] || (tmp[a[i]] == tmp[ans] && a[i] < ans)) {
                        ans = a[i];
                    }
                }

                // ????
                for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                    tmp[a[i]] = 0;
                }
                for(int i = l[bel[qr]] ; i <= qr ; ++ i) {
                    tmp[a[i]] = 0;
                }
                tmp[bak] = 0;
            }

            out[++ *out] = ans;
        }
    }
}

namespace Dsu {
    int head[2 * N], rest[2 * N], to[2 * N], tot;

    int c[N], most[N], sz[N], son[N], ans, cnt[N], l[N], r[N], seq[N], fa[N];

    vector<int> id[N];

    void add(int u, int v) {
        // insert an edge (u, v)
        to[++ tot] = v;
        rest[tot] = head[u];
        head[u] = tot;
        // printf("%d[%d, %d] -> %d[%d, %d]\n", u, l[u], r[u], v, l[v], r[v]);
    }

    void dfs(int u, int fa) {
        // get the son and the size and the l and the r
        sz[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v == fa) continue;
            dfs(v, u);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) son[u] = v;
        }
    }

    int calc = 0;

    void ins(int l, int r) {
        // insert the contribute in dfs sequnce [l, r]
        for(int i = l ; i <= r ; ++ i) {
            
            // ++ calc;

            ++ cnt[c[i]];
            if(cnt[c[i]] > cnt[ans] || (cnt[c[i]] == cnt[ans] && c[i] < ans)) ans = c[i];
        }
    }

    void del(int l, int r) {
        // delete the contribute in dfs sequnce [l,r]
        ans = 0;
        for(int i = l ; i <= r ; ++ i) {

            // ++ calc;

            cnt[c[i]] = 0;
        }
    }

    void sol(int u, int fa) {
        // solve the subtree u
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v == son[u] || v == fa) continue;
            sol(v, u);
            del(l[v], r[v]);
        }
        ans = 0;

        if(son[u]) {
            sol(son[u], u);
            int sl = l[son[u]], sr = r[son[u]];
            if(l[u] <= sl - 1) ins(l[u], sl - 1);
            if(sr + 1 <= r[u]) ins(sr + 1, r[u]);
        } else {
            ins(l[u], r[u]);
        }

        // ins(l[u], l[u]); // ?????

        most[u] = ans;
    }

    struct Q {
        int l, r, id;
    } q[N];

    bool operator < (Q x, Q y) {
        return x.l == y.l ? x.r > y.r : x.l < y.l;
    }

    void build() {
        // build the queries
        sort(q + 1, q + 1 + m);

        int rt = 1;
        l[1] = q[1].l, r[1] = q[1].r;
        id[1].push_back(q[1].id);
        for(int i = 2 ; i <= m ; ++ i) {
            int cl = q[rt].l, cr = q[rt].r;
            int nowl = q[i].l, nowr = q[i].r;
            l[i] = nowl, r[i] = nowr;
            if(cl == nowl && cr == nowr) {
                // ???
                id[rt].push_back(q[i].id);
            } else if(nowl > cr) {
                // ????
                while(rt && fa[rt] && q[rt].r < nowr) rt = fa[rt];
                fa[i] = rt;
                add(rt, i), add(i, rt);
                rt = i;
                id[i].push_back(q[i].id);
            } else if(cl <= nowl && nowr <= cr) {
                // ????
                fa[i] = rt;
                add(rt, i), add(i, rt);
                rt = i;
                id[i].push_back(q[i].id);
            }
        }
    }

    void main() {
        // read the data
        for(int i = 1 ; i <= n ; ++ i) scanf("%d", &c[i]);
        for(int i = 1 ; i <= m ; ++ i) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
        q[++ m] = (Q) {1, n, 0};

        build();

        // apply the methods
        dfs(1, 0);
        sol(1, 0);

        for(int i = 1 ; i <= m ; ++ i) {
            for(int j = 0 ; j < id[i].size() ; ++ j) {
                out[id[i][j]] = most[i];
            }
        }
        -- m;

        // printf("calc = %d\n", calc);

    }
}

namespace Sol {
    // map<ll, ll> mp[2];
    // ll ans, sum[N], p;
    // void st(ll x, ll y) {
    //     mp[p][x] = max(mp[p][x], y);
    // }
    // void main() {
    //     for(int i = 1 ; i <= n ; ++ i) sum[i] = sum[i - 1] + out[i];
    //     st(out[n], n);
    //     ans = out[n] + out[n];
    //     for(int i = n - 1 ; i ; -- i) {
    //         p ^= 1;
    //         mp[p].clear();
    //         st(out[i], i);
    //         ans = max(ans, out[i] + out[i]);
    //         for(map<ll, ll> :: iterator it = mp[p ^ 1].begin() ; it != mp[p ^ 1].end() ; ++ it) {
    //             st(out[i] & (it -> first), it -> second);
    //             ans = max(ans, (out[i] & (it -> first)) + sum[it -> second] - sum[i - 1]);
    //         }
    //     }
    //     printf("%lld\n", ans);
    // }
    
    struct T {
        int val, r;
    } a[2][N], tmp[N];
    bool operator < (T x, T y) {
        return x.val == y.val ? x.r > y.r : x.val < y.val;
    }
    int p, t[2], last, lll;
    ll ans, sum[N];
    void main() {
        a[0][0] = a[1][0] = (T) {-1, 0};

        for(int i = 1 ; i <= n ; ++ i) sum[i] = sum[i - 1] + out[i];
        a[p][++ t[p]] = (T) {out[n], n}; // st(out[n], n);
        ans = out[n] + out[n];
        for(int i = n - 1 ; i ; -- i) {
            // mp[p].clear();
            last = p;
            t[p ^= 1] = 0;
            a[p][++ t[p]] = (T) {out[i], i}; // st(out[i], i);
            ans = max(ans, (ll) out[i] + out[i]);
            // for(map<ll, ll> :: iterator it = mp[p ^ 1].begin() ; it != mp[p ^ 1].end() ; ++ it) {
            //     st(out[i] & (it -> first), it -> second);
            //     ans = max(ans, (out[i] & (it -> first)) + sum[it -> second] - sum[i - 1]);
            // }
            if(t[last]) {
                sort(a[last] + 1, a[last] + 1 + t[last]);
                lll = 0;
                for(int j = 1 ; j <= t[last] ; ++ j) {
                    if(a[last][j].val != a[last][j - 1].val) tmp[++ lll] = a[last][j];
                }
                for(int j = 1 ; j <= lll ; ++ j) {
                    a[p][++ t[p]] = (T) {out[i] & tmp[j].val, tmp[j].r};  // st(out[i] & (it -> first), it -> second);
                    ans = max(ans, (ll) (out[i] & tmp[j].val) + sum[tmp[j].r] - sum[i - 1]);
                }
            }
        }
        printf("%lld\n", ans);
    }
}

int main() {
    scanf("%d%d%d", &T, &n, &m);
    if(T <= 6) {
        FenKuai :: main();
    } else {
        Dsu :: main();
    }
    n = m;
    for(int i = 1 ; i <= n ; ++ i) {printf("%lld", out[i]); if(i < n) putchar(' ');} puts("");
    Sol :: main();
}
