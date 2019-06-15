#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

int n;
vector<int> g[N];
int fa[N], sz[N], f[N]; // 最大子连通块
int acc[N][22], dep[N];
int getlca(int u, int v) {
    // printf("u = %d, v = %d\n", u, v);
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[acc[u][i]] >= dep[v]) {
            u = acc[u][i];
        }
    }
    // printf("u = %d, v = %d\n", u, v);
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(acc[u][i] != acc[v][i]) {
            u = acc[u][i];
            v = acc[v][i];
        }
    }
    // printf("u = %d, v = %d\n", u, v);
    return acc[u][0];
}
int cnt[N], fsec[N];
void dfs(int u) {
    acc[u][0] = fa[u];
    for(int i = 1 ; i <= 20 ; ++ i) {
        acc[u][i] = acc[acc[u][i - 1]][i - 1];
    }
    dep[u] = dep[fa[u]] + 1;
    sz[u] = 1;
    for(int v: g[u]) {
        dfs(v);
        sz[u] += sz[v];
        if(sz[v] > f[u]) {
            fsec[u] = f[u];
            f[u] = sz[v];
            cnt[u] = 1;
        } else if(sz[v] == sz[u]) {
            ++ cnt[u];
        }
    }
    sort(g[u].begin(), g[u].end(), [&] (int i, int j) { return sz[i] < sz[j]; });
}
int getson(int u, int v) {
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[acc[u][i]] > dep[v]) {
            u = acc[u][i];
        }
    }
    return u;
}

const int T = N * 20;
int lc[T], rc[T], sum[T], rt[N], tot;
void modify(int lst, int now, int l, int r, int pos) {
    lc[now] = lc[lst], rc[now] = rc[lst], sum[now] = sum[lst] + 1;
    int mid = (l + r) >> 1;
    if(l == r) {
        return ;
    } else if(pos <= mid) {
        modify(lc[lst], lc[now] = ++ tot, l, mid, pos);
    } else {
        modify(rc[lst], rc[now] = ++ tot, mid + 1, r, pos);
    }
}

int ask(int L, int R, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    int s = sum[R] - sum[L];
    if(!s) return 0;
    if(ql <= l && r <= qr) {
        return s;
    } else if(qr <= mid) {
        return ask(lc[L], lc[R], l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc[L], rc[R], mid + 1, r, ql, qr);
    } else {
        return
            ask(lc[L], lc[R], l, mid, ql, mid) + ask(rc[L], rc[R], mid + 1, r, mid + 1, qr);
    }
}

int dfn[N], lef[N], rig[N], clk, seq[N];
void go_dfn(int u) {
    dfn[u] = lef[u] = ++ clk;
    seq[clk] = sz[u];
    for(int v: g[u]) {
        go_dfn(v);
    }
    rig[u] = clk;
}

int ask(int l, int r, int ql, int qr) {
    if(l > r || ql > qr) return 0;
    return ask(rt[l - 1], rt[r], 1, n, ql, qr);
}

int bit[N];
void add(int x, int y) {
    for( ; x <= n ; x += x & -x) {
        bit[x] += y;
    }
}
int ask(int x) {
    int r = 0;
    for( ; x ; x -= x & -x) {
        r += bit[x];
    }
    return r;
}
void SEGINS(int pos, int val) {
    add(pos, val);
}
int SEGASK(int ql, int qr) {
    ql = max(ql, 1);
    qr = min(qr, n);
    if(ql > qr) return 0;
    return ask(qr) - ask(ql - 1);
}

namespace NEKO {

    /*

    1. 如果有至少两个连通块都是最大值，那么无论怎么修改都有一个最大值没变，此时不会改变最大值
    2. 那么只有一个连通块是最大值，那么更新后的最大值不会超过当前的次大值
       考虑最大值mx和最小值mn，现在需要从最大值的中减去一个子树s，最小化 max(mx-s,mn+s)
       考虑二分答案 p，那么就要求 mx-s <= p && mn + s <= p => mx-p <= s <= p-mn
       主席树判断最大值的那个位置能否取到即可

    */

    int ans[N];
    void dfs(int u) {

        // 先把 u 扔进SEG中去
        SEGINS(sz[u], 1);

        int res = max(n - sz[u], f[u]);

        map<int, int> cnt;
        if(u != 1) {
            cnt[n - sz[u]] ++;
        }
        for(int v: g[u]) {
            cnt[sz[v]] ++;
        }

        if(g[u].size()) {
            // 起码也得有个儿子吧
            
            if((-- cnt.end()) -> second >= 2) {
                // 最大值是改不了了
            } else {
                int mx = (-- cnt.end()) -> first;
                int mn = cnt.begin() -> first;

                int smx = 0;
                if(cnt.size() == 2) {
                    // 就两个值
                    auto it = *cnt.begin();
                    if(it.second >= 2) {
                        smx = it.first;
                    }
                } else {
                    smx = (-- (-- cnt.end())) -> first;
                }

                if(mx == f[u]) {
                    // 最大值是 u 的子树
                    int v = * -- g[u].end();
                    int l = lef[v] + 1, r = rig[v];
                    if(l <= r) {
                        // 能选点
                        int mn = sz[g[u][0]];
                        if(u != 1) {
                            mn = min(mn, n - sz[u]);
                        }

                        int L = 0, R = n;
                        while(L <= R) {
                            int mid = (L + R) >> 1;

                            // mx-s <= p && mn + s <= p => mx-p <= s <= p-mn
                            int flag = ask(l, r, mx - mid, mid - mn);

                            if(flag) {

                                if(0 && u == 2 && max(mid, smx) == 3) {
                                    puts("ans3!");
                                }

                                res = min(res, max(mid, smx));
                                R = mid - 1;
                            } else {
                                L = mid + 1;
                            }
                        }
                    }
                } else {
                    // 最大值是 u 的外侧

                    // mx-s <= p && mn + s <= p => mx-p <= s <= p-mn
                    int mn = 0;
                    if(g[u].size()) {
                        mn = sz[g[u][0]];
                    }

                    int l1 = 1, r1 = lef[u];
                    int l2 = rig[u] + 1, r2 = n;
                    int L = 0, R = n;
                    while(L <= R) {
                        int mid = (L + R) >> 1;

                        int flag =
                            ask(l1, r1, mx - mid, mid - mn)
                          + ask(l2, r2, mx - mid, mid - mn)
                          - SEGASK(mx - mid, mid - mn)
                          + SEGASK(mx - mid + sz[u], mid - mn + sz[u]);
                          // s = sz[p] - sz[u]

                          if(0 && u == 2 && flag) {
                              printf("[%d, %d]: %d\n", l1, r1, ask(l1, r1, mx - mid, mid - mn));
                              printf("[%d, %d]: %d\n", l2, r2, ask(l2, r2, mx - mid, mid - mn));
                              printf("-%d\n", SEGASK(mx - mid, mid - mn));
                              printf("+%d\n", SEGASK(mx - mid + sz[u], mid - mn + sz[u]));
                          }

                        if(flag) {

                            if(0 && u == 2 && max(mid, smx) == 3) {
                                printf("mid = %d, smx = %d\n", mid, smx);
                                puts("ans3!!");
                            }

                            res = min(res, max(mid, smx));
                            R = mid - 1;
                        } else {
                            L = mid + 1;
                        }
                    }
                }
            }
        }
        ans[u] = res;

        for(int v: g[u]) {
            dfs(v);
        }

        // 从SEG中删掉u
        SEGINS(sz[u], -1);
    }

    void neko() {
        go_dfn(1);
        for(int i = 1 ; i <= n ; ++ i) {
            modify(rt[i - 1], rt[i] = ++ tot, 1, n, seq[i]);
        }
        dfs(1);
        for(int i = 1 ; i <= n ; ++ i) {
            printf("%d\n", ans[i]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 2, f ; i <= n ; ++ i) {
        scanf("%d", &f);
        g[f].emplace_back(i);
        fa[i] = f;
    }
    dfs(1);

    NEKO :: neko();
    return 0;

    if(n <= 2000) {

        for(int i = 1 ; i <= n ; ++ i) {
            // 删了i
            int res = max(n - sz[i], f[i]);
            multiset<int> s;
            if(i != 1) {
                s.emplace(n - sz[i]);
            }
            for(int j: g[i]) s.emplace(sz[j]);
            if(s.size() > 1) {
                for(int j = 1 ; j <= n ; ++ j) {
                    if(j != 1 && j != i && fa[j] != i) {
                        int k = getlca(i, j);
                        if(k == i) {
                            // 在 i 的子树中
                            int p = getson(j, i);
                            s.erase(s.find(sz[p]));
                            s.insert(sz[p] - sz[j]);
                            res = min(res, max(*--s.end(), *s.begin() + sz[j]));
                            
                            s.insert(sz[p]);
                            s.erase(s.find(sz[p] - sz[j]));
                        } else if(k == j) {
                            // j是i的祖先
                            s.erase(s.find(n - sz[i]));
                            s.insert(n - sz[j]);
                            int val = sz[j] - sz[i];
                            res = min(res, max(*--s.end(), *s.begin() + val));
                            s.insert(n - sz[i]);
                            s.erase(s.find(n - sz[j]));
                        } else {
                            // 不在 i 的子树中
                            s.erase(s.find(n - sz[i]));
                            s.insert(n - sz[i] - sz[j]);
                            res = min(res, max(*--s.end(), *s.begin() + sz[j]));
                            s.insert(n - sz[i]);
                            s.erase(s.find(n - sz[i] - sz[j]));
                        }
                    }
                }
            }
            printf("%d\n", res);
        }
    } else {
        NEKO :: neko();
    }
}
