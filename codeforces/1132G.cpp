#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 10;

int n, k, a[N];
vector<int> g[N];
int sta[N], top, dep[N];

int dfn[N], dfn_end[N], clk;

int val[N];

void dfs(int u) {
    dfn[u] = ++ clk;
    val[clk] = dep[u];
    for(int v: g[u]) {
        dfs(v);
    }
    dfn_end[u] = clk;
}

int mx[N * 10], tag[N * 10];
const int inf = -0xcfcfcfcf;

#define lc (id << 1)
#define rc (id << 1 | 1)

void push(int id) {
    if(tag[id]) {
        tag[lc] += tag[id], tag[rc] += tag[id];
        mx[id] += tag[id], tag[id] = 0;
    }
}

void upd(int id) {
    push(lc), push(rc);
    mx[id] = max(mx[lc], mx[rc]);
}

void modify(int id, int l, int r, int ql, int qr, int val) {
    int mid = (l + r) >> 1;
    push(id);
    if(ql <= l && r <= qr) {
        tag[id] += val;
        return ;
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, val);
    } else if(ql >= mid + 1) {
        modify(rc, mid + 1, r, ql, qr, val);
    } else {
        modify(lc, l, mid, ql, mid, val);
        modify(rc, mid + 1, r, mid + 1, qr, val);
    }
    upd(id);
}

int ans[N];

int main() {
    memset(mx, 0xcf, sizeof mx);
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = n ; i ; -- i) {
        while(top && a[sta[top]] <= a[i]) -- top;
        dep[i] = dep[sta[top]] + 1;
        g[sta[top]].push_back(i);
        // printf("%d -> %d\n", sta[top], i);
        sta[++ top] = i;
    }
    dfs(0);


    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("%d ", dep[i]);
    // } puts("");

    int L = n - k + 1, R = n;
    for(int i = L ; i <= R ; ++ i) {
        modify(1, 1, clk, dfn[i], dfn[i], inf + dep[i]);
    }
    for(int i = 1 ; i <= n - k + 1 ; ++ i) {
        push(1), ans[i] = mx[1];
        // printf("-1: [%d, %d]\n", dfn[R], dfn_end[R]);
        modify(1, 1, clk, dfn[R], dfn_end[R], -1);
        modify(1, 1, clk, dfn[L - 1], dfn[L - 1], inf + dep[L - 1]);
        -- R, -- L;
    }
    for(int i = n - k + 1 ; i ; -- i) {
        printf("%d ", ans[i]);
    }
}
