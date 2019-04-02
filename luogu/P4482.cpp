// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int GLON = 4e5 + 10;

int n, m, ans[GLON];
char str[GLON];

struct QUERY {
    int l, r;
} qrys[GLON];

struct SAM {
    int p, q, np, nq, ch[GLON][26], last, cnt, pre[GLON], len[GLON], pos[GLON], rev[GLON];
    SAM() { last = cnt = 1; }
    int nd(int l) { return len[++ cnt] = l, cnt; }
 
    void ins(int c, int id) {
        pre[last = np = nd(len[p = last] + 1)] = 1;
        pos[id] = np, rev[np] = id;
        while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
        if(p) {
            pre[np] = q = ch[p][c];
            if(len[p] + 1 != len[q]) {
                pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
            }
        }
    }
} sam;

const int N = GLON * 30, inf = 0x3f3f3f3f;
struct SEGTREE {
    int lc[N], rc[N], root[GLON], tot, mn[N];
    SEGTREE() {
        mn[0] = inf;
    }
    void ins(int &x, int l, int r, int pos, int val) {
        if(!x) x = ++ tot, mn[x] = inf;
        mn[x] = min(mn[x], val);
        int mid = (l + r) >> 1;
        if(l == r) {
            return ;
        } else if(pos <= mid) {
            ins(lc[x], l, mid, pos, val);
        } else {
            ins(rc[x], mid + 1, r, pos, val);
        }
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        int z = ++ tot;
        mn[z] = min(mn[x], mn[y]);
        lc[z] = merge(lc[x], lc[y]);
        rc[z] = merge(rc[x], rc[y]);
        return z;
    }
    int merge_del(int x, int y) {
        if(!x || !y) return x | y;
        mn[x] = min(mn[x], mn[y]);
        lc[x] = merge_del(lc[x], lc[y]);
        rc[x] = merge_del(rc[x], rc[y]);
        return x;
    }
    int ask(int x, int l, int r, int ql, int qr, int val) {
        int mid = (l + r) >> 1, res = 0;
        if(!x || ql > r || qr < l || mn[x] >= val || ql > qr) return 0;
        if(l == r) return l;
        res = ask(rc[x], mid + 1, r, ql, qr, val);
        if(res) return res;
        res = ask(lc[x], l, mid, ql, qr, val);
        if(res) return res;
        return 0;
    }
} tree_1, tree_2;

vector<int> g[GLON];

int fa[GLON], top[GLON], sz[GLON], son[GLON];

void dfs(int u) {
    sz[u] = 1;
    for(int v: g[u]) {
        fa[v] = u;
        dfs(v);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
}

void gettop(int u) {
    if(sam.rev[u]) {
        tree_1.ins(tree_1.root[u], 1, n, sam.rev[u], sam.rev[u]);
    }
    if(!top[u]) top[u] = u;
    if(son[u]) {
        top[son[u]] = top[u];
        gettop(son[u]);
    }
    for(int v: g[u]) {
        if(v != son[u]) {
            gettop(v);
        }
        tree_1.root[u] = tree_1.merge(tree_1.root[u], tree_1.root[v]);
    }
}

void run(int x, int l, int r, int tar) {
    int mid = (l + r) >> 1;
    if(l == r) {
        tree_2.ins(tree_2.root[tar], 1, n, l, l - sam.len[tar]);
        return;
    }
    if(tree_1.lc[x]) run(tree_1.lc[x], l, mid, tar);
    if(tree_1.rc[x]) run(tree_1.rc[x], mid + 1, r, tar);
}

vector<int> ask[GLON];
void go(int u) {
    for(int v: g[u]) {
        go(v);
    }
    if(u == top[u]) {
        int x = u;
        while(x) {
            for(int y: g[x]) {
                if(y != son[x]) {
                    run(tree_1.root[y], 1, n, x);
                }
            }
            for(int y: ask[x]) {
                int l = qrys[y].l, r = qrys[y].r;
                ans[y] = max(ans[y], tree_2.ask(tree_2.root[x], 1, n, l, r - 1, l));
            }
            if(son[x]) {
                // tree_2.root[son[x]] = tree_2.merge_del(tree_2.root[son[x]], tree_2.root[x]);
                tree_2.root[son[x]] = tree_2.merge(tree_2.root[son[x]], tree_2.root[x]);
            }
            x = son[x];
        }
    }
}

int main() {

    scanf("%s", str + 1);
    n = strlen(str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        sam.ins(str[i] - 'a', i);
    }
    for(int i = 2 ; i <= sam.cnt ; ++ i) {
        g[sam.pre[i]].push_back(i);
    }
    dfs(1);

    gettop(1);

    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int l, r; scanf("%d%d", &l, &r);
        qrys[i] = (QUERY) { l, r };
        int u = sam.pos[r];
        while(u) {
            ask[u].push_back(i);
            ans[i] = max(ans[i], tree_1.ask(tree_1.root[u], 1, n, l, r - 1, l + sam.len[u]));
            u = fa[top[u]];
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        tree_2.ins(tree_2.root[sam.pos[i]], 1, n, i, 0);
    }
    go(1);

    for(int i = 1 ; i <= m ; ++ i) {
        if(!ans[i]) {
            puts("0");
        } else {
            printf("%d\n", ans[i] - qrys[i].l + 1);
        }
    }
}
