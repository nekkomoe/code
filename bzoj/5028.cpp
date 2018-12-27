#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5 * 2;
 
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
 
int head[N], rest[N], to[N], tmp[N], sz[N], son[N], top[N], fa[N], deep[N], cnt, dfn[N], n, q, val[N];
 
struct st {
    int x1, g, xn, d, l, r, tag;
} p[N * 10];
 
void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
 
void push(int u) {
    if(p[u].tag) {
        p[u << 1].tag += p[u].tag, p[u << 1 | 1].tag += p[u].tag;
        p[u].x1 += p[u].tag;
        p[u].xn += p[u].tag; 
        if(p[u].l == p[u].r) {
            p[u].xn = p[u].g = p[u].d = p[u].x1;
        } else {
            p[u].d = gcd(p[u].x1, p[u].g);
        }
        p[u].tag = 0;
    }
}
 
void update(int u) {
    push(u), push(u << 1), push(u << 1 | 1);
    if(p[u].l == p[u].r) {
        p[u].x1 = val[p[u].l];
        p[u].xn = p[u].x1;
        p[u].g = p[u].x1;
        p[u].d = p[u].x1;
    } else {
        p[u].x1 = p[u << 1].x1;
        p[u].xn = p[u << 1 | 1].xn;
        if(p[u << 1].l == p[u << 1].r) {
            if(p[u << 1 | 1].l == p[u << 1 | 1].r) {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = max(a, b) - min(a, b);
            } else {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = gcd(max(a, b) - min(a, b), p[u << 1 | 1].g);
            }
        } else {
            if(p[u << 1 | 1].l == p[u << 1 | 1].r) {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = gcd(p[u << 1].g, max(a, b) - min(a, b));
            } else {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = gcd(gcd(p[u << 1].g, max(a, b) - min(a, b)), p[u << 1 | 1].g);
            }
        }
        p[u].d = gcd(p[u].x1, p[u].g);
    }
}
 
void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r;
    int mid = (l + r) >> 1;
    if(l == r) {
        p[u].x1 = p[u].xn = p[u].g = p[u].d = val[l];
        return ;
    }
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    update(u);    
}
 
int ask(int u, int ql, int qr) {
    push(u);
    int l = p[u].l, r = p[u].r;
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr) {
        return p[u].d;
    }
    return gcd(ask(u << 1, ql, qr), ask(u << 1 | 1, ql, qr));
}
 
void change(int u, int ql, int qr, int x) {
    push(u);
    int l = p[u].l, r = p[u].r;
    if(ql > r || qr < l) return ;
    if(ql <= l && r <= qr) {
        p[u].tag += x;
        return ;
    }
    change(u << 1, ql, qr, x), change(u << 1 | 1, ql, qr, x);
    update(u);
}
 
void dfs(int u) {
    sz[u] = 1;
    deep[u] = deep[fa[u]] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u]) {
            fa[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) son[u] = v;
        }
    }
}
 
void dfs(int u, int tp) {
    dfn[u] = ++ cnt;
    val[cnt] = tmp[u];
    top[u] = tp;
    if(son[u]) dfs(son[u], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u] && v != son[u]) {
            dfs(v, v);
        }
    }
}
 
int query(int u, int v) {
    int ret = 0;
    while(top[u] != top[v]) {
        if(deep[top[u]] < deep[top[v]]) swap(u, v);
        ret = gcd(ret, ask(1, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if(deep[u] > deep[v]) swap(u, v);
    ret = gcd(ret, ask(1, dfn[u], dfn[v]));
    return ret;
}
 
void modify(int u, int v, int x) {
    while(top[u] != top[v]) {
        if(deep[top[u]] < deep[top[v]]) swap(u, v);
        change(1, dfn[top[u]], dfn[u], x);
        u = fa[top[u]];
    }
    if(deep[u] > deep[v]) swap(u, v);
    change(1, dfn[u], dfn[v], x);
}
 
int main() {
//    freopen("data.in", "r", stdin);
    scanf("%d%d", &n, &q);
    for(int i = 1, u, v ; i < n ; ++ i) {
        u = i, v = i + 1;
        add(u, v), add(v, u);
    }
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &tmp[i]);
    dfs(1), dfs(1, 1);
    build(1, 1, n);
    for(int i = 1 ; i <= q ; ++ i) {
        int op, u, v, x;
        scanf("%d%d%d", &op, &u, &v);
        if(u > v) swap(u, v);
        if(op == 1) {
            printf("%d\n", query(u, v));
        } else {
            scanf("%d", &x);
            modify(u, v, x);
        }
    }
}
?
