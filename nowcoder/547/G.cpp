#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

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
        int c = 0, x = 0;
        int flag = 0;
        while(!isdigit(c)) c = xchar(), flag |= c == '-';
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return flag ? -x : x;
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
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

const int N = 2e6 + 10;

int n, m, root;

int head[N], rest[N * 2], to[N * 2];
inline void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
int dfn[N], dfn_end[N], clk, dep[N], val[N];

int fa[N], top[N], sz[N], son[N];

inline void dfs(int u) {
    dep[u] = dep[fa[u]] + 1;
    dfn[u] = ++ clk;
    sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u]) {
            fa[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if(sz[v] >= sz[son[u]]) {
                son[u] = v;
            }
        }
    }
    dfn_end[u] = clk;
}

inline void gettp(int u, int tp) {
    top[u] = tp;
    if(son[u]) gettp(son[u], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u] && v != son[u]) {
            gettp(v, v);
        }
    }
}

struct BIT {
    ll bit[N];
    inline void add(int x, ll y) {
        for( ; x <= n ; x += x & -x) {
            bit[x] += y;
        }
    }
    inline void add(int l, int r, ll y) {
        add(l, y), add(r + 1, -y);
    }
    inline ll ask(int x) {
        ll res = 0;
        for( ; x ; x -= x & -x) {
            res += bit[x];
        }
        return res;
    }
} depbit, valbit;

inline ll askval(int u) {
    return dep[u] * depbit.ask(dfn[u]) + valbit.ask(dfn[u]);
}

inline int getlca(int u, int v) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main() {
    n = io(), m = io(), root = io();
    for(int i = 1 ; i <= n ; ++ i) val[i] = io();
    for(int i = 1 ; i < n ; ++ i) {
        int u = io(), v = io();
        add(u, v), add(v, u);
    }
    dfs(root);
    gettp(root, root);

    for(int i = 1 ; i <= n ; ++ i) {
        valbit.add(dfn[i], dfn_end[i], val[i]);
    }
    while(m --) {
        int op = io(), u = io(), x = io();
        if(op == 1) {
            valbit.add(dfn[u], dfn_end[u], x);
        } else if(op == 2) {
            valbit.add(dfn[u], dfn_end[u], (ll) (1 - dep[u]) * x);
            depbit.add(dfn[u], dfn_end[u], x);
        } else {
            int d = getlca(u, x);
            io(askval(u) + askval(x) - askval(d) - askval(fa[d]));
        }
    }
}
