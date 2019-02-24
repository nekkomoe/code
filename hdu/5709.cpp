#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10;

int n, m, col[N];
vector<int> g[N];

const int NN = 1e7 + 10;
int nd_cnt, sum[NN], lc[NN], rc[NN];

int dep[N], rt1[N], rt2[N];

void modify(int &x, int l, int r, int pos, int val) {
    int mid = (l + r) >> 1;
    int y = ++ nd_cnt;
    lc[y] = lc[x], rc[y] = rc[x], sum[y] = sum[x], x = y;
    sum[x] += val;
    if(l == r) return ;
    if(pos <= mid) modify(lc[x], l, mid, pos, val);
    else modify(rc[x], mid + 1, r, pos, val);
}

int merge1(int x, int y, int l, int r, int u) {
    if(!x || !y) return x | y;
    int z = ++ nd_cnt;
    if(l == r) {
        sum[z] = min(sum[x], sum[y]);
        modify(rt2[u], 1, n, max(sum[x], sum[y]), -1);
    } else {
        int mid = (l + r) >> 1;
        lc[z] = merge1(lc[x], lc[y], l, mid, u);
        rc[z] = merge1(rc[x], rc[y], mid + 1, r, u);
    }
    return z;
}

int merge2(int x, int y) {
    if(!x || !y) return x | y;
    int z = ++ nd_cnt;
    sum[z] = sum[x] + sum[y];
    lc[z] = merge2(lc[x], lc[y]);
    rc[z] = merge2(rc[x], rc[y]);
    return z;
}

void dfs(int u) {
    modify(rt1[u], 1, n, col[u], dep[u]);
    modify(rt2[u], 1, n, dep[u], 1);

    for(int v: g[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
        rt1[u] = merge1(rt1[u], rt1[v], 1, n, u);
        rt2[u] = merge2(rt2[u], rt2[v]);
    }
}

void go(int x, int l, int r) {
    if(!x) return ;
    if(l == r) {
        if(sum[x]) {
            printf("(%d):%d ", l, sum[x]);
        }
        return ;
    }
    int mid = (l + r) >> 1;
    go(lc[x], l, mid);
    go(rc[x], mid + 1, r);
}

int ask(int x, int l, int r, int ql, int qr) {
    if(!x) return 0;
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) return sum[x];
    else if(qr <= mid) return ask(lc[x], l, mid, ql, qr);
    else if(ql >= mid + 1) return ask(rc[x], mid + 1, r, ql, qr);
    else return ask(lc[x], l, mid, ql, mid) + ask(rc[x], mid + 1, r, mid + 1, qr); 
}

void runprog() {
    int ans = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &col[i]);
        g[i].clear();
        rt1[i] = rt2[i] = 0;
    }
    for(int i = 2 ; i <= n ; ++ i) {
        int fa; scanf("%d", &fa);
        g[fa].push_back(i);
    }
    dep[1] = 1, dfs(1);
    for(int i = 1, x, d ; i <= m ; ++ i) {
        scanf("%d%d", &x, &d);
        // #ifdef ONLINE_JUDGE
        x ^= ans, d ^= ans;
        // #endif
        printf("%d\n", ans = ask(rt2[x], 1, n, dep[x], min(n, dep[x] + d)));
        // go(rt2[x], 1, n), puts("");
    }
    for(int i = 1 ; i <= nd_cnt ; ++ i) {
        lc[i] = rc[i] = sum[i] = 0;
    }
    nd_cnt = 0;
}

int main() {
// #ifndef ONLINE_JUDGE
    // freopen("data.in", "r", stdin);
// #endif
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
