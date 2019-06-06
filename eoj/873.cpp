#include <bits/stdc++.h>
using namespace std;
typedef int ll;

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

const int N = 4e6 + 10, M = 5e6 + 10;
int len[N], b[M], ans, n, m, clk, pos[N], p[23][N], lg[N], t[M];
struct Dat {
    int x, y;
    Dat(int x = 0, int y = 0) : x(x), y(y) { }
} f[N];
vector<pair<int, int> > g[N];

inline int gemx(int l, int r) {
    if(l > r) swap(l, r);
    register int k = lg[r - l + 1];
    return min(p[k][l], p[k][r - (1 << k) + 1]) << 1;
}
inline int getdis(int u, int v) { return !u || !v ? (u > 0) << (v > 0) : t[u] + t[v] - gemx(b[u], b[v]); }

inline void dfs(int u, int fa) {
    p[0][pos[u] = ++ clk] = len[u];
    for(register auto &e: g[u]) {
        register int v = e.first, w = e.second;
        if(v != fa) {
            len[v] = len[u] + w;
            dfs(v, u);
            p[0][++ clk] = len[u];
        }
    }
}

inline int getdis(Dat a) { return getdis(a.x, a.y); }

inline Dat merge(Dat a, int b, int dp) {
    int d1 = getdis(a.x, b), d2 = getdis(a.y, b);
    Dat res = (Dat) { a.x, b };
    if(d1 < d2) swap(d1, d2), res = (Dat) { a.y, b };
    ans = max(ans, d1 - dp);
    if(getdis(a.x, a.y) > d1) res = a;
    return res;
}

inline Dat merge(Dat a, Dat b, int dp) {
    Dat res = (Dat) { a.x, b.x }, nr;
    register int d = getdis(res), nd;

    if((nd = getdis(nr = (Dat) { a.x, b.y })) > d)
        res = nr, d = nd;

    if((nd = getdis(nr = (Dat) { a.y, b.x })) > d)
        res = nr, d = nd;

    if((nd = getdis(nr = (Dat) { a.y, b.y })) > d)
        res = nr, d = nd;

    ans = max(ans, d - dp);

    if((nd = getdis(nr = (Dat) { a.x, a.y })) > d)
        res = nr, d = nd;

    if((nd = getdis(nr = (Dat) { b.x, b.y })) > d)
        res = nr, d = nd;

    return res;
}

inline void go(int u, int fa) {
    register int l = len[u] << 1;
    register Dat &res = f[u];
    for(register auto &e: g[u]) {
        register int v = e.first, w = e.second;
        if(v != fa) {
            go(v, u);
            res = merge(res, f[v], l);
        }
    }
}

int main() {
    n = io(), m = io();
    for(register int i = 1, u, v, w ; i < n ; ++ i) {
        u = io(), v = io(), w = io();
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dfs(1, 0);
    for(register int i = 2 ; i <= clk ; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(register int j = 1 ; j <= 22 ; ++ j) {
        register int i = 1, lim = clk - (1 << j) + 1;

        for( ; i <= lim ; i += 4) {
            #define calc(i) p[j][i] = min(p[j - 1][i], p[j - 1][i + (1 << (j - 1))])

            calc(i);
            calc(i + 1);
            calc(i + 2);
            calc(i + 3);

        }

        for( ; i <= lim ; ++ i) {
            p[j][i] = min(p[j - 1][i], p[j - 1][i + (1 << (j - 1))]);
        }
    }
    for(register int i = 1, u, v ; i <= m ; ++ i) {
        u = io();
        b[i] = pos[v = io()];
        t[i] = len[u] + len[v];
        f[u] = merge(f[u], i, len[u] << 1);
    }
    go(1, 0);
    io(ans);
}
