#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// #define printf
// #define puts
const int N = 2e6 + 10;

char str[N];
int n, k1, k2;

struct SAM {
    int tstlen;
    int last, samcnt, ch[N][26], len[N], pre[N], pos[N], nps[N];
    SAM() {
        last = samcnt = 1;
    }
    int nd(int l) {
        return len[++ samcnt] = l, samcnt;
    }
    void ins(int c, int ids) {
        int np, p, q, nq;
        pre[np = last = nd(len[p = last] + 1)] = 1;
        pos[ids] = np;
        nps[np] = ids;
        while(p && !ch[p][c]) {
            ch[p][c] = np;
            p = pre[p];
        }
        if(p) {
            pre[np] = q = ch[p][c];
            if(len[p] + 1 != len[q]) {
                nq = nd(len[p] + 1);
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                pre[nq] = pre[q];
                pre[np] = pre[q] = nq;
                while(p && ch[p][c] == q) {
                    ch[p][c] = nq;
                    p = pre[p];
                }
            }
        }
    }
    vector<vector<int> > g;
    vector<int> dep;
    vector<int> val;
    vector<tuple<int, int> > eds;
    void build() {
        g.resize(samcnt + 5, vector<int> ());
        for(int i = 1 ; i <= samcnt ; ++ i) {
            if(pre[i]) {
                g[pre[i]].emplace_back(i);
                eds.emplace_back(pre[i], i);
            }
        }
    }
    void erase(int k) {
        val.resize(samcnt + 5);
        for(int i = 1 ; i <= samcnt ; ++ i) {
            if(len[i] > k) {
                len[i] = 0;
            }
            val[i] = len[i];
        }
    }
    // int getlca(int u, int v) {
    //     if(dep[u] < dep[v]) {
    //         swap(u, v);
    //     }
    //     while(dep[pre[u]] >= dep[v]) {
    //         u = pre[u];
    //     }
    //     if(u == v) {
    //         return u;
    //     }
    //     while(pre[u] != pre[v]) {
    //         u = pre[u], v = pre[v];
    //     }
    //     return pre[u];
    // }

    void getdep(int u, int fa) {
        dep[u] = dep[fa] + 1;
        for(int v: g[u]) {
            getdep(v, u);
        }
    }

    void gettrideg(int k) {
        eds.clear();
        for(int i = samcnt ; i ; -- i) {

            // for(int j: g[i]) {
            //     eds.emplace_back(i, j);
            // }
            // continue;

            if(g[i].size()) {
                int lst = i;
                for(int j: g[i]) {
                    ++ samcnt;
                    len[samcnt] = len[i];
                    eds.emplace_back(lst, samcnt);
                    eds.emplace_back(samcnt, j);
                    lst = samcnt;
                }
            }
        }
        val.resize(samcnt + 5);
        for(int i = 1 ; i <= samcnt ; ++ i) {
            if(len[i] > k) {
                len[i] = 0;
            }
            val[i] = len[i];
        }
        g = vector<vector<int> > (samcnt + 5);
        for(auto e: eds) {
            int u, v; tie(u, v) = e;
            g[u].emplace_back(v);
            // cout << u << " -> " << v << endl;
        }
        dep.resize(samcnt + 5);
        getdep(1, 0);
        // for(int i = 1 ; i <= samcnt ; ++ i) {
        //     assert(g[i].size() <= 3);
        // }
    }
} A, B;

int head[N], rest[N], to[N], tot = 1, trabac[N];
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int ban[N];
int edrt, vlrt, sz[N], glosz;
void getsz(int u, int fa) {
    sz[u] = 1;
    // int deg = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        // ++ deg;
        int v = to[i];
        if(!ban[i] && v != fa) {
            getsz(v, u);
            sz[u] += sz[v];
            int updval = max(sz[v], glosz - sz[v]);
            if(updval <= vlrt) {
                vlrt = updval;
                edrt = i;
            }
        }
    }
    // assert(deg <= 3);
}

const int SEGN = 8e6 + 10;
int ch[SEGN][2], rt[N], til[N], trcnt;
ull tsz[SEGN], tval[SEGN];

void modify(int x, int way) {
    ch[til[x]][way] = ++ trcnt;
    til[x] = trcnt;

    // cout << trcnt << endl;

}
int tag[N], clk;

// int deps;

void dfs(int u, int fa, int mx, int ty) {
    modify(u, ty);
    // printf("modify %d -> son %d(%d)\n", u, til[u], ty);

    // ++ deps;
    // printf("dep = %d\n", deps);

    if(tag[u] == clk) {
        mx = A.val[u];
    }

    if(A.nps[u]) {
        // if(u == 4) {
        //     printf("setsize %d\n", til[u]);
        // }
        tsz[til[u]] = 1;
        if(ty == 0) {
            tval[til[u]] = mx;
            // printf("edit val = %d\n", mx);
        }
    }

    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!ban[i] && v != fa) {
            dfs(v, u, mx, ty);
        }
    }

    // -- deps;
}

void sol(int e) {
    if(!e) {
        return ;
    }
    ban[e] = ban[e ^ 1] = 1;

    // printf("dep = %d\n", dps);

    int u = to[e], v = to[e ^ 1];
    if(A.dep[u] > A.dep[v]) {
        swap(u, v);
    }

    int x = u;
    ++ clk;
    while(1) {
        tag[x] = clk;
        if(!to[trabac[x]] || ban[trabac[x]]) {
            break;
        }
        x = to[trabac[x]];
    }
    dfs(x, 0, 0, 0);
    dfs(v, 0, 0, 1);

    vector<tuple<int, int> > nxt;
    nxt.emplace_back(to[e], sz[to[e]]);
    nxt.emplace_back(to[e ^ 1], glosz - sz[to[e]]);
    for(auto t: nxt) {
        int v; tie(v, glosz) = t;
        edrt = 0, vlrt = 0x3f3f3f3f, getsz(v, 0), sol(edrt);
    }
}

void edge_div_tree() {
    n = A.samcnt;
    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("val[%d] = %d\n", i, A.val[i]);
    // }
    for(auto e: A.eds) {
        int u, v; tie(u, v) = e;
        // u -> v
        add(u, v), add(v, u);
        trabac[v] = tot; // 往上走的边
        // printf("%d -> %d\n", u, v);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        rt[i] = til[i] = ++ trcnt;
    }
    glosz = n, edrt = 0, vlrt = 0x3f3f3f3f, getsz(1, 0), sol(edrt);
}

ull ans, coef;

int merge(int x, int y) {
    if(!x || !y) {
        return x | y;
    }
    coef += tval[ch[x][0]] * tsz[ch[y][1]];
    coef += tval[ch[y][0]] * tsz[ch[x][1]];
    // printf("in x = %d, y = %d\n", x, y);
    // printf("%lld * %lld with %d, %d\n", tval[ch[x][0]], tsz[ch[y][1]], ch[x][0], ch[y][1]);
    // printf("%lld * %lld with %d, %d\n", tval[ch[y][0]], tsz[ch[x][1]], ch[y][0], ch[x][1]);
    tsz[x] += tsz[y];
    tval[x] += tval[y];
    ch[x][0] = merge(ch[x][0], ch[y][0]);
    ch[x][1] = merge(ch[x][1], ch[y][1]);
    return x;
}

/*
2 * (1) + 1 * (1 + 2) = 5
*/

int dfs(int u) {
    // printf("ano val[%d] = %d, pos = %d\n", u, B.val[u], B.nps[u]);
    int res = rt[A.pos[B.nps[u]]];
    for(int v: B.g[u]) {
        // printf("ano link %d -> %d\n", u, v);
        int resv = dfs(v);
        coef = 0;
        // int tx = res, ty = resv;
        res = merge(res, resv);
        ans += coef * B.val[u];
        // printf("(%d,%d)(%d) coef = %lld, %d\n", tx, ty, u, coef, B.val[u]);
    }
    return res;
}

/*
aaab
1 4
*/

/*
(1, 3) : 1, 1
(1, 4) : 0, 0
(2, 3) : 1, 2
(2, 4) : 0, 0
(3, 4) : 0, 0
3
*/

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    A.tstlen = B.tstlen = n;
    for(int i = 1 ; i <= n ; ++ i) {
        A.ins(str[i] - 'a', i);
    }
    for(int i = n ; i >= 1 ; -- i) {
        B.ins(str[i] - 'a', i);
    }
    scanf("%d%d", &k1, &k2);
    A.build(), B.build();
    A.gettrideg(k1), B.erase(k2);

    // puts("posA: ");
    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("posA[%d] = %d\n", i, A.pos[i]);
    // }
    // puts("posB: ");
    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("posB[%d] = %d\n", i, B.pos[i]);
    // }

    edge_div_tree();

    // for(int i = 1 ; i <= trcnt ; ++ i) {
    //     printf("pts(%d): sz = %d, val = %d\n", i, tsz[i], tval[i]);
    // }
    // puts("");

    dfs(1);

    cout << ans << endl;
}
