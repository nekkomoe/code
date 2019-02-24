#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, lim = 1e5 + 5;

int n, a[N], b[N];
vector<int> g[N];
ll ans[N];

int root[N], nd_cnt, lc[N], rc[N];

struct LINE {
    ll k, b; int id;
    ll f(ll x) {
        return k * x + b;
    }
} neko[N];

bool neko_greater(LINE a, LINE b, ll x) {
    return a.id ? a.f(x) > b.f(x) : 1;
}

void insert(int &x, int l, int r, LINE ln) {
    if(!x) x = ++ nd_cnt;
    int mid = (l + r) >> 1;
    if(neko_greater(neko[x], ln, mid)) swap(neko[x], ln);
    if(l == r || neko[x].k == ln.k || !ln.id) return ;
    double val = (double) (neko[x].b - ln.b) / (ln.k - neko[x].k);
    if(val < l || val > r) return ;
    if(ln.k > neko[x].k) insert(lc[x], l, mid, ln);
    else insert(rc[x], mid + 1, r, ln);
}

int merge(int x, int y, int l, int r) {
    if(!x || !y) return x | y;
    insert(x, l, r, neko[y]);
    int mid = (l + r) >> 1;
    lc[x] = merge(lc[x], lc[y], l, mid);
    rc[x] = merge(rc[x], rc[y], mid + 1, r);
    return x;
}

LINE ask(int x, int l, int r, int pos) {
    if(l == r) return neko[x];
    int mid = (l + r) >> 1;
    LINE tmp = pos <= mid ? ask(lc[x], l, mid, pos) : ask(rc[x], mid + 1, r, pos);
    return neko_greater(tmp, neko[x], pos) ? neko[x] : tmp;
}

void dfs(int u, int fa) {
    for(int v: g[u]) {
        if(v == fa) continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v], 1, 2 * lim);
    }
    int id = ask(root[u], 1, lim * 2, a[u] + lim).id;
    ans[u] = (ll) b[id] * a[u] + ans[id];
    ll k = b[u], b = ans[u] - lim * k;
    insert(root[u], 1, lim * 2, (LINE) { k, b, u });
}

int main() {
//    freopen("data.in", "r", stdin);
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &b[i]);
    for(int i = 2 ; i <= n ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld ", ans[i]);
    }
}

