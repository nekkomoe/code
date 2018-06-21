#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int head[N], rest[2 * N], to[2 * N], tot;

inline void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }

struct Mat {
    ll x[3];
    inline Mat() { memset(x, 0, sizeof x); }
    inline Mat operator * (Mat b) {
        Mat c;
        c.x[0] = x[0] + b.x[0],
        c.x[1] = x[1] + b.x[1],
        c.x[2] = x[0] * b.x[1] + x[2] + b.x[2];
        return c;
    }
} mat[N * 10], op1, op2;

int fa[N], top[N], pos[N], cnt, sz[N], son[N];

inline void dfs(int u) {
    sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u]) continue;
        fa[v] = u, dfs(v), sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}

inline void dfs(int u, int tp) {
    top[u] = tp, pos[u] = ++ cnt;
    if(son[u]) dfs(son[u], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs(v, v);
    }
}

#define lc (id << 1)
#define rc (id << 1 | 1)

inline void push(int id) {
    if(mat[id].x[0] || mat[id].x[1] || mat[id].x[2])
        mat[lc] = mat[lc] * mat[id],
        mat[rc] = mat[rc] * mat[id],
        memset(mat[id].x, 0, 3 * sizeof(ll));
}

inline void modify(int id, int l, int r, int ql, int qr, Mat &mt) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        mat[id] = mat[id] * mt;
        return ;
    }
    push(id);
    if(ql <= mid) modify(lc, l, mid, ql, qr, mt);
    if(qr >  mid) modify(rc, mid + 1, r, ql, qr, mt);
}

inline void query(int &pos) {
    for(int id = 1, l = 1, r = cnt, mid ; l <= r ; (push(id), pos <= mid) ? (r = mid, id = lc) : (l = mid + 1, id = rc)) {
        if(l == r) { printf("%lld\n", mat[id].x[2]); return ; }
        mid = (l + r) >> 1;
    }
}

int n, m;

template<typename T> inline void read(T &x) {
    char c = x = 0; bool f = 0;
    while(!isdigit(c))
        f |= (c = getchar()) == '-';
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if(f) x = -x;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);

    read(n);
    for(int i = 1, u, v ; i < n ; ++ i)
        read(u), read(v), add(u, v), add(v, u);
    dfs(1), dfs(1, 1);
    read(m);
    for(int i = 1, op, x, y ; i <= m ; ++ i) {
        read(op), read(x);
        if(op == 1)
            for(read(op1.x[0]) ; x ; x = fa[top[x]])
                modify(1, 1, cnt, pos[top[x]], pos[x], op1);
        else if(op == 2)
            for(read(op2.x[1]) ; x ; x = fa[top[x]])
                modify(1, 1, cnt, pos[top[x]], pos[x], op2);
        else query(pos[x]);
    }
}
