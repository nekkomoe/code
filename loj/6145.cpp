#include <bits/stdc++.h>
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

const int N = 100000 + 10;

int n, q; 

struct E {
    int v, w;
};

vector<E> G[N];

struct T {
    int id, x;
};

vector<T> que[N * 10];

#define lc (id << 1)
#define rc (id << 1 | 1)
void poi(int id, int l, int r, int ql, int qr, T t) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        que[id].push_back(t);
    } else if(qr <= mid) {
        poi(lc, l, mid, ql, qr, t);
    } else if(ql >= mid + 1) {
        poi(rc, mid + 1, r, ql, qr, t);
    } else {
        poi(lc, l, mid, ql, mid, t);
        poi(rc, mid + 1, r, mid + 1, qr, t);
    }
}

int ans[N], beg_dfn[N], end_dfn[N], clk, dep[N], len[N];
int fa[N][21];

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i)
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i)
        if(fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

void getdfn(int u, int fa) {
    :: fa[u][0] = fa;
    for(int i = 1 ; i <= 20 ; ++ i)
        :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    
    beg_dfn[u] = ++ clk;
    dep[u] = dep[fa] + 1;
    for(E e: G[u]) {
        int v = e.v, w = e.w;
        if(v == fa) continue;
        len[v] = len[u] + w;
        getdfn(v, u);
    }
    end_dfn[u] = clk;
}

int a[N * 10], top, root, spe[N];
int cmp(int x, int y) { return beg_dfn[x] < beg_dfn[y]; }

const int inf = 0x3f3f3f3f;
int f[N], h[N];

int head[N], rest[N * 2], to[N * 2], w[N * 2], tot;

int thev[N], thew[N], the_top;

namespace TreeDP {
    void dfs(int u, int fa) {
        
//        cerr << "u = " << u << endl;
        
        f[u] = inf;
        if(spe[u]) f[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i], w = :: w[i];
            if(v == fa) continue;
            dfs(v, u);
            f[u] = min(f[u], f[v] + w);
        }
    }
    
    void go(int u, int fa) {
        if(u == root) h[u] = inf;
        if(spe[u]) h[u] = 0;
        
        the_top = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i], w = :: w[i];
            if(v == fa) continue;
            thev[++ the_top] = v;
            thew[the_top] = w;
        }
        
        int themn = inf;
        for(int i = 1 ; i <= the_top ; ++ i) {
            int v = thev[i], w = thew[i];
            h[v] = h[u] + w;
            h[v] = min(h[v], themn + w);
            themn = min(themn, f[v] + w);
        }
        themn = inf;
        for(int i = the_top ; i >= 1 ; -- i) {
            int v = thev[i], w = thew[i];
            h[v] = min(h[v], themn + w);
            themn = min(themn, f[v] + w);
        }
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v == fa) continue;
            go(v, u);
        }
    }
    
    void sol(int root) {
        
        
        dfs(root, 0);
        
        
        go(root, 0);
        
    }
}

void add(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
    to[++ tot] = u, :: w[tot] = w, rest[tot] = head[v], head[v] = tot;
}

int sta[N], statop;

void dfs(int id, int l, int r) {
    
//    cerr << l << ' ' << r << endl;
    
    int mid = (l + r) >> 1;
    if(que[id].size()) {
        top = 0;
        for(int i = l ; i <= r ; ++ i) {
            a[++ top] = i;
            spe[i] = 1;
        }
        for(T t: que[id]) {
            a[++ top] = t.x;
        }
        sort(a + 1, a + 1 + top, cmp);
        top = unique(a + 1, a + 1 + top) - a - 1;
        
//        assert(top <= N * 10);
        
        for(int i = top ; i >= 2 ; -- i) {
            a[++ top] = getlca(a[i], a[i - 1]);
        }
        sort(a + 1, a + 1 + top, cmp);
        top = unique(a + 1, a + 1 + top) - a - 1;
        
        tot = 0;
        for(int i = 1 ; i <= top ; ++ i) {
            head[a[i]] = 0;
        }
        root = a[1];
        
        statop = 0;
        for(int i = 1 ; i <= top ; ++ i) {
            int u = a[i];
            while(statop && end_dfn[sta[statop]] < beg_dfn[u]) -- statop;
            if(statop) {
                add(sta[statop], u, len[u] - len[sta[statop]]);
            }
            sta[++ statop] = u;
        }
        
        TreeDP :: sol(root);
        
        
        for(T t: que[id]) {
            int ansid = t.id, u = t.x;
            ans[ansid] = min(ans[ansid], min(f[u], h[u]));
        }
        
        for(int i = l ; i <= r ; ++ i) spe[i] = 0;
    }
    
    if(l != r) dfs(lc, l, mid), dfs(rc, mid + 1, r);
}

int main() {
    n = io();
    int _fafasum = 0;
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        u = io(), v = io(), w = io();
        G[u].push_back((E) { v, w });
        G[v].push_back((E) { u, w });
        _fafasum += w;
    }
    getdfn(1, 0);
    q = io();
    
    for(int i = 1 ; i <= q ; ++ i) ans[i] = _fafasum;
    
    for(int i = 1, l, r, x ; i <= q ; ++ i) {
        l = io(), r = io(), x = io();
        poi(1, 1, n, l, r, (T) { i, x });
    }
    dfs(1, 1, n);
    for(int i = 1 ; i <= q ; ++ i) {
        io(ans[i]);
    }
}
