#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cctype>
#include <bitset>

using namespace std;

typedef long long ll;

const int N = 200010;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int sz[N], son[N], dfn[N], clk, fa[N], top[N], deep[N], tmp[N], a[N];

void dfs(int u) {
    sz[u] = 1;
    deep[u] = deep[fa[u]] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u]) {
            fa[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if(sz[son[u]] < sz[v]) son[u] = v;
        }
    }
}

void dfs(int u, int tp) {
    top[u] = tp, a[dfn[u] = ++ clk] = tmp[u];
    if(son[u]) dfs(son[u], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u] && v != son[u]) {
            dfs(v, v);
        }
    }
}

typedef long long ll;

ll sum[N * 10], tag[N * 10];

#define lc (id << 1)

#define rc (id << 1 | 1)

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) sum[id] = a[l];
    else build(lc, l, mid), build(rc, mid + 1, r), sum[id] = sum[lc] + sum[rc];
}

void push(int id, int l, int r) { if(tag[id]) tag[lc] += tag[id], tag[rc] += tag[id], sum[id] += tag[id] * (r - l + 1), tag[id] = 0; }

ll query(int id, int l, int r, int ql, int qr) {
    push(id, l, r);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return sum[id];
    } else if(ql > r || qr < l) {
        return 0;
    } else {
        return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
    }
}

void modify(int id, int l, int r, int ql, int qr, ll x) {
    push(id, l, r);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        tag[id] += x;
    } else if(ql > r || qr < l) {
        return ;
    } else {
        modify(lc, l, mid, ql, qr, x), modify(rc, mid + 1, r, ql, qr, x);
        push(lc, l, mid), push(rc, mid + 1, r), sum[id] = sum[lc] + sum[rc];
    }
}

int n, m;

ll query(int u) {
    ll res = 0;
    while(u) {
        res += query(1, 1, n, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &tmp[i]);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1);
    dfs(1, 1);
    build(1, 1, n);
    for(int i = 1, op, x, a ; i <= m ; ++ i) {
        scanf("%d%d", &op, &x); if(op != 3) scanf("%d", &a);
        if(op == 1) {
            modify(1, 1, n, dfn[x], dfn[x], a);
        } else if(op == 2) {
            modify(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, a);
        } else {
            printf("%lld\n", query(x));
        }
    }
}

