#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void space(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

const int N = 5e5 + 10;

int n, q, dep[N]; ll len[N];

struct E { int v, w; };
vector<E> g[N];

int lef[N], rig[N], clk, sta[N], poi[N][25], bin[N];
inline void dfs(int u, int f) {
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

inline int mer(int x, int y) {
    return dep[x] < dep[y] ? x : y;
}

inline void init() {
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

inline int getlca(int u, int v) {
    if(u == v) return u;
    int l = lef[u], r = lef[v];
    if(l > r) swap(l, r);
    int k = bin[r - l + 1];
    return mer(poi[l][k], poi[r - (1 << k) + 1][k]);
    // if(dep[u] < dep[v]) swap(u, v);
    // for(int i = 20 ; ~ i ; -- i)
    //     if(dep[poi[u][i]] >= dep[v])
    //         u = poi[u][i];
    // if(u == v) return u;
    // for(int i = 20 ; ~ i ; -- i)
    //     if(poi[u][i] != poi[v][i])
    //         u = poi[u][i], v = poi[v][i];
    // return poi[u][0];
}

ll getdis(int u, int v) {
    // printf("lca(%d, %d) = %d\n", u, v, getlca(u, v));
    return len[u] + len[v] - 2 * len[getlca(u, v)];
}

#define lc (id << 1)
#define rc (id << 1 | 1)

pair<ll, pair<int, int> > merge(pair<int, int> x, pair<int, int> y) {
    return max(
        max(make_pair(getdis(x.first, x.second), x),
            make_pair(getdis(y.first, y.second), y)),
        max(
            max(make_pair(getdis(x.first, y.first), make_pair(x.first, y.first)),
                make_pair(getdis(x.second, y.second), make_pair(x.second, y.second))),
            max(make_pair(getdis(x.first, y.second), make_pair(x.first, y.second)),
                make_pair(getdis(x.second, y.first), make_pair(x.second, y.first))))
    );
}

pair<int, int> pts[N * 10];
void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        pts[id] = make_pair(l, l);
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        pair<int, int> x = pts[lc], y = pts[rc];
        pts[id] = merge(x, y).second;
    }
}

pair<int, int> ask(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return pts[id];
    } else if(qr <= mid) {
        return ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc, mid + 1, r, ql, qr);
    } else {
        return merge(ask(lc, l, mid, ql, mid), ask(rc, mid + 1, r, mid + 1, qr)).second;
    }
}

int main() {
    n = io();
    // scanf("%d", &n);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        u = io(), v = io(), w = io();
        // scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((E) { v, w }), g[v].push_back((E) { u, w });
    }
    dfs(1, 0);
    init();
    build(1, 1, n);
    q = io();
    // scanf("%d", &q);

    for(int i = 1, a, b, c, d ; i <= q ; ++ i) {
        a = io(), b = io(), c = io(), d = io();
        // scanf("%d%d%d%d", &a, &b, &c, &d);

        pair<int, int> x = ask(1, 1, n, a, b), y = ask(1, 1, n, c, d);
        ll ans = max(
            max(getdis(x.first, y.first),
                getdis(x.first, y.second)),
            max(getdis(x.second, y.first),
                getdis(x.second, y.second))
        );

        // ll ans = merge().first;


        // auto t = merge(ask(1, 1, n, a, b), ask(1, 1, n, c, d));
        // printf("%d, %d\n", t.second.first, t.second.second);

        // printf("[%d, %d], [%d, %d]\n", );
        // printf("%lld\n", getdis(28, 41));

        // ll ans = 0;
        // for(int j = a ; j <= b ; ++ j) {
        //     for(int k = c ; k <= d ; ++ k) {
        //         ans = max(ans, getdis(j, k));
        //     }
        // }
        io(ans);
        // printf("%lld\n", ans);
        // break;
    }
}
