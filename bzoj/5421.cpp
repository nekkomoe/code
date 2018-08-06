#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10;
typedef long long ll;
int n, m;
ll sum[N * 4], tag[N * 4];
#define lc (id << 1)
#define rc (id << 1 | 1)
void push(int id, int l, int r) {
    if(tag[id]) {
        tag[lc] += tag[id], tag[rc] += tag[id];
        sum[id] += tag[id] * (r - l + 1);
        tag[id] = 0;
    }
}
void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
    sum[id] = sum[lc] + sum[rc];
}
void modify(int id, int l, int r, int ql, int qr, ll x) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) tag[id] += x;
    else if(qr <= mid) modify(lc, l, mid, ql, qr, x), update(id, l, r);
    else if(ql >= mid + 1) modify(rc, mid + 1, r, ql, qr, x), update(id, l, r);
    else modify(lc, l, mid, ql, mid, x), modify(rc, mid + 1, r, mid + 1, qr, x), update(id, l, r);
}
ll query(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) return sum[id];
    else if(qr <= mid) return query(lc, l, mid, ql, qr);
    else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
    else return query(lc, l, mid, ql, mid) + query(rc, mid + 1, r, mid + 1, qr);
}
int head[N * 2], rest[N * 2], to[N * 2], tot;
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
int dl[N], dr[N], clk;
void dfs(int u, int fa) {
    dl[u] = ++ clk;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
    }
    dr[u] = clk;
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    for(int i = 1, x, y ; i <= m ; ++ i) {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'Q') {
            scanf("%d", &x);
            printf("%lld\n", query(1, 1, n, dl[x], dr[x]));
        } else {
            scanf("%d%d", &x, &y);
            modify(1, 1, n, dl[x], dr[x], y);
        }
    }
}
