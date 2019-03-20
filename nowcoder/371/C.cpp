#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
vector<int> g[N];
int n, m, fa[N][22];

int dfn[N], dfn_end[N], clk, dep[N];
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    :: fa[u][0] = fa;
    for(int i = 1 ; i <= 20 ; ++ i) {
        :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    }
    dfn[u] = ++ clk;
    for(int v: g[u]) {
        if(v != fa) {
            dfs(v, u);
        }
    }
    dfn_end[u] = clk;
}

int get_son(int u, int v) {
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[v][i]] > dep[u]) {
            v = fa[v][i];
        }
    }
    return v;
}

struct RECT {
    int x1, y1, x2, y2;
};
vector<RECT> rect;

void add_rect(int x1, int y1, int x2, int y2) {
    // printf("%d %d %d %d\n", x1, y1, x2, y2);
    rect.push_back((RECT) { x1, y1, x2, y2 });
}

void add_range(int l, int r, int x, int y) {
    if(1 <= l && l <= r && r <= n
    && 1 <= x && x <= y && y <= n) {
        // printf("[%d, %d] - [%d, %d]\n", l, r, x, y);
        ++ r, ++ y;
        add_rect(x, r, y, l);
        swap(l, x), swap(r, y);
        add_rect(x, r, y, l);
    }
}

struct T {
    int l, r, h, d;
};
bool operator < (T a, T b) {
    return a.h < b.h;
}

vector<T> tmp;

ll sum[N * 10], cnt[N * 10];

#define lc (id << 1)
#define rc (id << 1 | 1)

void upd(int id, int l, int r) {
    if(cnt[id]) sum[id] = r - l + 1;
    else if(l == r) sum[id] = 0;
    else sum[id] = sum[lc] + sum[rc];
}

void modify(int id, int l, int r, int ql, int qr, int val) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        cnt[id] += val;
        upd(id, l, r);
        return ;
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, val);
    } else if(ql >= mid + 1) {
        modify(rc, mid + 1, r, ql, qr, val);
    } else {
        modify(lc, l, mid, ql, mid, val);
        modify(rc, mid + 1, r, mid + 1, qr, val);
    }
    upd(id, l, r);
}


ll get_rect_merge() {
    ll res = 0;
    for(RECT rct: rect) {
        int x1 = rct.x1, y1 = rct.y1, x2 = rct.x2, y2 = rct.y2;
        tmp.push_back((T) { x1, x2, y1, 1 });
        tmp.push_back((T) { x1, x2, y2, -1 });
    }
    int lim = n + 1;
    sort(tmp.begin(), tmp.end());

    for(int i = 0 ; i < tmp.size() - 1 ; ++ i) {
        int l = tmp[i].l, r = tmp[i].r;
        if(l < r) modify(1, 1, lim, l, r - 1, tmp[i].d);
        res += sum[1] * (tmp[i + 1].h - tmp[i].h);
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        add_range(i, i, i, i);
    }

    dfs(1, 0);

    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("%d: [%d, %d]\n", i, dfn[i], dfn_end[i]);
    // }

    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        assert(u != v);
        if(dep[u] > dep[v]) swap(u, v);
        if(dfn[u] <= dfn[v] && dfn[v] <= dfn_end[u]) {
            int d = get_son(u, v);
            // [1, dfn[u] - 1]
            // [dfn_end[u] + 1, n]
            // [dfn[v], dfn_end[v]]
            add_range(1, dfn[d] - 1, dfn[v], dfn_end[v]);
            add_range(dfn_end[d] + 1, n, dfn[v], dfn_end[v]);
        } else {
            // [dfn[u], dfn_end[u]]
            // [dfn[v], dfn_end[v]]
            add_range(dfn[u], dfn_end[u], dfn[v], dfn_end[v]);
        }
    }
    ll sum = get_rect_merge();

    ll ans = (ll) n * n - sum;
    printf("%lld\n", ans / 2);
}
