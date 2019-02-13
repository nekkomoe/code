#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m, q, w[N];

multiset<int> son_w[N];

vector<pair<int, int> > E;

int head[N], rest[N], to[N], tot;
void add(int u, int v) {
    // printf("%d -> %d\n", u, v);
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int sta[N], dfn[N], low[N], clk, cnt, cat[N];
void tarj(int u, int fa) {
    cat[u] = 1;
    static int top = 0;
    dfn[u] = low[u] = ++ clk, sta[++ top] = u;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            tarj(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                ++ cnt;
                E.push_back(make_pair(u, cnt));
                int neko;
                do {
                    neko = sta[top --];
                    E.push_back(make_pair(neko, cnt));
                } while(neko != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int fa[N], dep[N], top[N], sz[N], son[N], rev[N];

void dfs(int u, int fa) {
    sz[u] = 1;
    :: fa[u] = fa;
    dep[u] = dep[fa] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        if(!cat[u]) {
            son_w[u].insert(w[v]);
        }
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
    if(!cat[u]) {
        w[u] = *son_w[u].begin();
    }
}

void dfs_top(int u, int tp) {
    dfn[u] = ++ clk;
    rev[clk] = u;
    top[u] = tp;
    if(son[u]) dfs_top(son[u], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs_top(v, v);
    }
}

int mn[N];

#define lc (id << 1)
#define rc (id << 1 | 1)

void ST_build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        mn[id] = w[rev[l]];
    } else {
        ST_build(lc, l, mid), ST_build(rc, mid + 1, r);
        mn[id] = min(mn[lc], mn[rc]);
    }
}

void ST_modify(int id, int l, int r, int pos, int val) {
    int mid = (l + r) >> 1;
    if(l == r) {
        mn[id] = val;
        return ;
    } else if(pos <= mid) {
        ST_modify(lc, l, mid, pos, val);
    } else {
        ST_modify(rc, mid + 1, r, pos, val);
    }
    mn[id] = min(mn[lc], mn[rc]);
}

int ST_ask(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return mn[id];
    } else if(qr <= mid) {
        return ST_ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ST_ask(rc, mid + 1, r, ql, qr);
    }  else {
        return min(ST_ask(lc, l, mid, ql, mid), ST_ask(rc, mid + 1, r, mid + 1, qr));
    }
}

int getlca(int u, int v) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void TSP_modify(int u, int old_val, int new_val) {
    ST_modify(1, 1, cnt, dfn[u], new_val);
}

int TSP_ask(int u, int v) {
    int res = 1e9 + 10;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        // printf("ask %d -> %d\n", top[u], u);
        res = min(res, ST_ask(1, 1, cnt, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    // printf("ask %d -> %d\n", v, u);
    res = min(res, ST_ask(1, 1, cnt, dfn[v], dfn[u]));
    return res;
}

void runprog_init() {
    dfs(1, 0);
    clk = 0;
    dfs_top(1, 1);
    ST_build(1, 1, cnt);
}

void runprog_modify(int u, int val) {
    if(val == w[u]) return ;
    int old_val = w[u];
    w[u] = val;
    TSP_modify(u, old_val, val);
    if(fa[u]) {
        int fa = :: fa[u];
        son_w[fa].erase(son_w[fa].find(old_val));
        son_w[fa].insert(val);
        int new_val = *son_w[fa].begin();
        if(w[fa] != new_val) {
            TSP_modify(fa, w[fa], new_val);
            w[fa] = new_val;
        }
    }
}

int runprog_ask(int u, int v) {
    // printf("ask %d, %d\n", u, v);
    int res = TSP_ask(u, v);
    int lca = getlca(u, v);
    if(!cat[lca]) {
        int fa = :: fa[lca];
        res = min(res, w[fa]);
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &w[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    cnt = n;
    tarj(1, 0);
    // puts("---------");
    for(int i = 1 ; i <= n ; ++ i) head[i] = 0; tot = 0;
    for(int i = 0 ; i < E.size() ; ++ i) {
        int u = E[i].first, v = E[i].second;
        add(u, v), add(v, u);
    }
    runprog_init();
    // for(int i = 1 ; i <= cnt ; ++ i) {
    //     printf("%d, ", dfn[i]);
    // } puts("");
    // for(int u = 1 ; u <= cnt ; ++ u) {
    //     printf("w[%d] = %d, cat = %d\n", u, w[u], cat[u]);
    // }
    while(q --) {
        char op[10]; scanf("%s", op);
        if(op[0] == 'C') {
            int u, val; scanf("%d%d", &u, &val);
            runprog_modify(u, val);
        } else {
            int u, v; scanf("%d%d", &u, &v);
            printf("%d\n", runprog_ask(u, v));
        }
    }
}
