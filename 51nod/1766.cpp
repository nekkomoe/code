#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

int n, q, dep[N]; ll len[N];

struct E { int v, w; };
vector<E> g[N];

int lef[N], rig[N], clk, sta[N], poi[N][25], bin[N];
void dfs(int u, int f) {
    sta[++ clk] = u;
    lef[u] = clk;
    dep[u] = dep[f] + 1;
    for(E e: g[u]) {
        int v = e.v;
        if(v == f) continue;
        len[v] = len[u] + e.w;
        dfs(v, u);

        sta[++ clk] = u;
    }
}

int mer(int x, int y) {
    return dep[x] < dep[y] ? x : y;
}

void init() {
    bin[0] = -1;
    for(int i = 1 ; i <= clk ; ++ i) {
        poi[i][0] = sta[i];
        bin[i] = bin[i >> 1] + 1;
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= clk ; ++ i) {
            poi[i][j] = mer(poi[i][j - 1], poi[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int getlca(int u, int v) {
    if(u == v) return u;
    int l = lef[u], r = lef[v];
    if(l > r) swap(l, r);
    int len = r - l + 1;
    int k = bin[len];
    return mer(poi[l][k], poi[r - (1 << k) + 1][k]);
}

ll getdis(int u, int v) {
    return len[u] + len[v] - 2 * len[getlca(u, v)];
}

pair<ll, pair<int, int> > merge(vector<int> x, vector<int> y) {
    vector<int> z;
    for(int i = 0 ; i < x.size() ; ++ i) z.push_back(x[i]);
    for(int i = 0 ; i < y.size() ; ++ i) z.push_back(y[i]);
    vector<pair<ll, pair<int, int> > > res;
    for(int i = 0 ; i < z.size() ; ++ i) {
        int u = z[i];
        for(int j = 0 ; j < z.size() ; ++ j) {
            int v = z[j];
            res.push_back(make_pair(getdis(u, v), make_pair(u, v)));
        }
    }
    return *max_element(res.begin(), res.end());
}

#define lc (id << 1)
#define rc (id << 1 | 1)

vector<int> pts[N * 10];
void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        pts[id].push_back(l);
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        pair<int, int> res = merge(pts[lc], pts[rc]).second;
        pts[id].push_back(res.first);
        pts[id].push_back(res.second);
    }
}

vector<int> ask(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return pts[id];
    } else if(qr <= mid) {
        return ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc, mid + 1, r, ql, qr);
    } else {
        pair<int, int> res = merge(ask(lc, l, mid, ql, mid), ask(rc, mid + 1, r, mid + 1, qr)).second;
        vector<int> tmp;
        tmp.push_back(res.first);
        tmp.push_back(res.second);
        return tmp;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((E) { v, w }), g[v].push_back((E) { u, w });
    }
    dfs(1, 0);
    init();
    build(1, 1, n);
    scanf("%d", &q);
    for(int i = 1, a, b, c, d ; i <= q ; ++ i) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        vector<int> x = ask(1, 1, n, a, b), y = ask(1, 1, n, c, d);
        ll ans = 0;
        for(int i = 0 ; i < x.size() ; ++ i) {
            int u = x[i];
            for(int j = 0 ; j < y.size() ; ++ j) {
                int v = y[j];
                ans = max(ans, getdis(u, v));
            }
        }
        printf("%lld\n", ans);
    }
}
