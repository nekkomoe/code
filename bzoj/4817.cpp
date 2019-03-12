#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, m;
vector<int> g[N];
int lca_fa[N][22], dep[N], dfn[N], dfn_end[N], clk, rev[N], fa[N], ch[N][2];
void dfs(int u) {
    dfn[u] = ++ clk, rev[clk] = u;
    dep[u] = dep[lca_fa[u][0]] + 1;
    fa[u] = lca_fa[u][0];
    for(int i = 1 ; i <= 20 ; ++ i) {
        lca_fa[u][i] = lca_fa[lca_fa[u][i - 1]][i - 1];
    }
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v != lca_fa[u][0]) {
            lca_fa[v][0] = u;
            dfs(v);
        }
    }
    dfn_end[u] = clk;
}
int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[lca_fa[u][i]] >= dep[v]) {
            u = lca_fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(lca_fa[u][i] != lca_fa[v][i]) {
            u = lca_fa[u][i], v = lca_fa[v][i];
        }
    }
    return lca_fa[u][0];
}
int tag[N * 10], mx[N * 10];
#define lc (id << 1)
#define rc (id << 1 | 1)
void push(int id) {
    if(tag[id]) {
        tag[lc] += tag[id], tag[rc] += tag[id];
        mx[id] += tag[id], tag[id] = 0;
    }
}
void upd(int id) {
    push(id), push(lc), push(rc);
    mx[id] = max(mx[lc], mx[rc]);
}
int a[N];
void build(int id, int l, int r) {
    // for(int i = 1 ; i <= n ; ++ i) a[i] = dep[rev[i]];
    // return ;

    int mid = (l + r) >> 1;
    if(l == r) {
        mx[id] = dep[rev[l]];
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        upd(id);
    }
}
void modify(int id, int l, int r, int ql, int qr, int cat) {
    // for(int i = ql ; i <= qr ; ++ i) a[i] += cat;
    // return ;

    int mid = (l + r) >> 1;
    push(id);
    if(ql <= l && r <= qr) {
        tag[id] += cat;
        return ;
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, cat);
    } else if(ql >= mid + 1) {
        modify(rc, mid + 1, r, ql, qr, cat);
    } else {
        modify(lc, l, mid, ql, mid, cat);
        modify(rc, mid + 1, r, mid + 1, qr, cat);
    }
    upd(id);
}
int ask(int id, int l, int r, int ql, int qr) {
    // int res = 0;
    // for(int i = ql ; i <= qr ; ++ i) res = max(res, a[i]);
    // return res;

    int mid = (l + r) >> 1;
    push(id);
    if(ql <= l && r <= qr) {
        return mx[id];
    } else if(qr <= mid) {
        return ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc, mid + 1, r, ql, qr);
    } else {
        return max(ask(lc, l, mid, ql, mid), ask(rc, mid + 1, r, mid + 1, qr));
    }
}

int isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

int isrig(int x) {
    return ch[fa[x]][1] == x;
}

int getrt(int x) {
    while(ch[x][0]) x = ch[x][0];
    return x;
}

void rot(int x) {
    int y = fa[x], z = fa[y], k = isrig(x);
    fa[x] = z; if(!isroot(y)) ch[z][isrig(y)] = x;
    fa[ch[y][k] = ch[x][!k]] = y;
    fa[ch[x][!k] = y] = x;
}

void splay(int x) {
    for( ; !isroot(x) ; rot(x)) {
        if(!isroot(fa[x])) {
            rot(isrig(x) == isrig(fa[x]) ? fa[x] : x);
        }
    }
}

void access(int x) {
    for(int y = 0 ; x ; y = x, x = fa[x]) {
        splay(x);
        if(ch[x][1]) {
            int rt = getrt(ch[x][1]);
            modify(1, 1, n, dfn[rt], dfn_end[rt], 1);
        }
        if((ch[x][1] = y)) {
            int rt = getrt(ch[x][1]);
            modify(1, 1, n, dfn[rt], dfn_end[rt], -1);
        }
    }
}

void runprog() {
    int op; scanf("%d", &op);
    if(op == 1) {
        int x; scanf("%d", &x);
        access(x);
    } else if(op == 2) {
        int x, y; scanf("%d%d", &x, &y);
        int d = getlca(x, y);
        // printf("lca %d, %d = %d\n", x, y, d);
        printf("%d\n", ask(1, 1, n, dfn[x], dfn[x]) + ask(1, 1, n, dfn[y], dfn[y]) - 2 * ask(1, 1, n, dfn[d], dfn[d]) + 1);
    } else {
        int x; scanf("%d", &x);
        printf("%d\n", ask(1, 1, n, dfn[x], dfn_end[x]));
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs(1), build(1, 1, n);
    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("[%d, %d]\n", dfn[i], dfn_end[i]);
    // }
    while(m --) {
        runprog();
    }
}
