#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e6 + 10;
vector<int> g[N];

int n, R, root[N], nd_cnt, lc[N], rc[N], neko[N], a[N];

void insert(int &x, int l, int r, int pos, int val) {
    if(!x) x = ++ nd_cnt;
    int mid = (l + r) >> 1;
    neko[x] = val;
    if(l == r) return ;
    if(pos <= mid) insert(lc[x], l, mid, pos, val);
    else insert(rc[x], mid + 1, r, pos, val);
}

int merge(int x, int y) {
    if(!x || !y) return x | y;
    int z = ++ nd_cnt;
    neko[z] = min(neko[x], neko[y]);
    lc[z] = merge(lc[x], lc[y]);
    rc[z] = merge(rc[x], rc[y]);
    return z;
}

int ask(int x, int l, int r, int ql, int qr) {
    if(!x) return 1e9 + 10;
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) return neko[x];
    else if(qr <= mid) return ask(lc[x], l, mid, ql, qr);
    else if(ql >= mid + 1) return ask(rc[x], mid + 1, r, ql, qr);
    else return min(ask(lc[x], l, mid, ql, mid), ask(rc[x], mid + 1, r, mid + 1, qr));
}

int dep[N];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    insert(root[u], 1, n, dep[u], a[u]);
    for(int v: g[u]) {
        if(v == fa) continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v]);
    }
}

int main() {
//    freopen("data.in", "r", stdin);
    scanf("%d%d", &n, &R);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 2 ; i <= n ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(R, 0);
    int q, lastans = 0; scanf("%d", &q);
    while(q --) {
        int x, k; scanf("%d%d", &x, &k);
        x = ((ll) x + lastans) % n + 1;
        k = ((ll) k + lastans) % n;
        printf("%d\n", lastans = ask(root[x], 1, n, dep[x], min(n, dep[x] + k)));
    }
}

