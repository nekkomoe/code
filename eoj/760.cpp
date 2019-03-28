
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

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
        if (pos == len) exit(0);
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

int n, q, a[N];
vector<int> g[N];
vector<pair<int, int> > qrys[N];

ll ans[N];

const int T = N * 30;
int rt[N], ch[T][2], sz[T], fa[T], nek[T];
ll sum[T];
int tot;
inline int nd(ll val) {
    int x = ++ tot;
    ch[x][0] = ch[x][1] = fa[x] = 0;
    sz[x] = 1, nek[x] = sum[x] = val;
    return x;
}
inline void upd(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + nek[x];
}
inline int isrig(int x) { return ch[fa[x]][1] == x; }
inline void rot(int x) {
    int y = fa[x], z = fa[y], k = isrig(x);
    fa[x] = z; if(z) ch[z][isrig(y)] = x;
    fa[ch[y][k] = ch[x][!k]] = y;
    fa[ch[x][!k] = y] = x;
    upd(y), upd(x);
}
inline void splay(int &tar, int x) {
    for(int y = fa[x] ; y ; rot(x), y = fa[x]) {
        if(fa[y]) {
            rot(isrig(x) == isrig(y) ? y : x);
        }
    }
    tar = x;
}
inline void ins(int &u, int v) {
    if(!u) {
        u = v;
    } else if(nek[v] < nek[u]) {
        ins(ch[u][0], v), fa[ch[u][0]] = u;
    } else {
        ins(ch[u][1], v), fa[ch[u][1]] = u;
    }
    upd(u);
}
inline void insert(int &u, int v) {
    ins(u, v);
    splay(u, v);
}
inline void go(int u, int &tar) {
    if(!u) return ;
    int tmpch0 = ch[u][0], tmpch1 = ch[u][1];
    ch[u][0] = ch[u][1] = fa[u] = 0, sz[u] = 1, sum[u] = nek[u];
    insert(tar, u);
    go(tmpch0, tar);
    go(tmpch1, tar);
}
inline int merge(int u, int v) {
    if(!u || !v) return u || v;
    if(sz[u] > sz[v]) swap(u, v);
    go(u, v);
    return v;
}
inline ll ask(int u, int k) {
    return u ? sz[ch[u][0]] >= k ? ask(ch[u][0], k) : sum[ch[u][0]] + nek[u] + ask(ch[u][1], k - sz[ch[u][0]] - 1) : 0;
}
inline ll dfs(int u, int fa) {
    int val = a[u];
    while(val) {
        insert(rt[u], nd(val / 2 - val));
        val /= 2;
    }
    ll res = a[u];
    for(int v: g[u]) {
        if(v != fa) {
            res += dfs(v, u);
            rt[u] = merge(rt[u], rt[v]);
        }
    }
    for(auto t: qrys[u]) {
        ans[t.first] = res + ask(rt[u], t.second);
    }
    return res;
}

int main() {
    n = io(), q = io();
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = io();
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        u = io(), v = io();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1, u, k ; i <= q ; ++ i) {
        u = io(), k = io();
        qrys[u].push_back(make_pair(i, k));
    }
    dfs(1, 0);
    for(int i = 1 ; i <= q ; ++ i) {
        io(ans[i]);
    }
}
