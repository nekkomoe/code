#include "bits/stdc++.h"
using namespace std;

const int N = 2e6 + 10;

struct Mat {
    int a[2][2];
    Mat() { memset(a, 0, sizeof a); }
    int* operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i) {
            for(int j = 0 ; j < 2 ; ++ j) {
                for(int k = 0 ; k < 2 ; ++ k) {
                    c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return c;
    }
} mat[N], neko[N];

int head[N], rest[N], to[N];
void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
int dfn[N], pos[N], bot[N], clk, fa[N], val[N], sz[N], son[N], top[N], n, q;

int f[N][2], p[N];

void dfs_1(int u) {
    sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u]) continue;
        fa[v] = u;
        dfs_1(v);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) {
            son[u] = v;
        }

        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
    f[u][1] += p[u];
}

void dfs_2(int u, int tp) {
    top[u] = tp;
    dfn[pos[u] = ++ clk] = u;
    bot[u] = u;
    if(son[u]) {
        dfs_2(son[u], tp);
        bot[u] = bot[son[u]];
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs_2(v, v);
    }
}

#define lc (id << 1)
#define rc (id << 1 | 1)
Mat seg_ask(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return mat[id];
    } else if(qr <= mid) {
        return seg_ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return seg_ask(rc, mid + 1, r, ql, qr);
    } else {
        return seg_ask(lc, l, mid, ql, mid) * seg_ask(rc, mid + 1, r, mid + 1, qr);
    }
}
void seg_chg(int id, int l, int r, int pos) {
    int mid = (l + r) >> 1;
    if(l == r) {
        mat[id] = neko[l];
        return ;
    }
    if(pos <= mid) {
        seg_chg(lc, l, mid, pos);
    } else {
        seg_chg(rc, mid + 1, r, pos);
    }
    mat[id] = mat[lc] * mat[rc];
}
void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        int u = dfn[l];
        int f0 = 0, f1 = p[u];
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v == son[u] || v == fa[u]) continue;
            f0 += max(f[v][0], f[v][1]);
            f1 += f[v][0];
        }
        neko[l][0][0] = f0, neko[l][0][1] = f0;
        neko[l][1][0] = f1;
        mat[id] = neko[l];
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        mat[id] = mat[lc] * mat[rc];
    }
}

void modify(int u, int nya) {
    neko[pos[u]][1][0] += nya - p[u], p[u] = nya;
    while(u) {
        Mat pre = seg_ask(1, 1, n, pos[top[u]], pos[bot[u]]);
        seg_chg(1, 1, n, pos[u]);
        Mat aft = seg_ask(1, 1, n, pos[top[u]], pos[bot[u]]);
        u = fa[top[u]];
        int ps = pos[u];
        neko[ps][0][0] += max(aft[0][0], aft[1][0]) - max(pre[0][0], pre[1][0]);
        neko[ps][0][1] = neko[ps][0][0];
        neko[ps][1][0] += aft[0][0] - pre[0][0];
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &p[i]);
    }
    for(int i = 1 ; i < n ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs_1(1), dfs_2(1, 1), build(1, 1, n);

    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("%d %d\n", f[i][0], f[i][1]);
    // }

    for(int i = 1 ; i <= q ; ++ i) {
        int u, nya; scanf("%d%d", &u, &nya);
        modify(u, nya);
        Mat res = seg_ask(1, 1, n, pos[top[1]], pos[bot[1]]);
        printf("%d\n", max(res[0][0], res[1][0]));
    }
}
