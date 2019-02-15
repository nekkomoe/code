#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

struct FastIO {
    static const int S = 2e7;
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

const int N = 4e5 + 10, Q = 3e6 + 10, BIT = N, SEGN = 1e7, RMQ = 1e6 + 10;
int head[N], rest[N * 2], to[N * 2], tot;
inline void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
int n, q, a[N];

pair<int, int> ele[N]; int ele_cnt;

int dep[N], dfn[N], dfn_clk;
int mn[RMQ][20], mx[RMQ][20], lg[RMQ];
int tl[RMQ][20], lca_dfn[RMQ], lca_clk;

int VAL_CNT, banmn, banmx;
const int inf = 0x3f3f3f3f;
struct ASK { int L, R; } mem[Q];
struct P { int x, y, w; };
P pts[SEGN]; int pts_cnt;
ll output[Q];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = ++ dfn_clk;
    lca_dfn[u] = ++ lca_clk;
    tl[lca_clk][0] = dep[u];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        tl[++ lca_clk][0] = dep[u];
    }
}

inline int getmin(int a, int b) { return dfn[a] < dfn[b] ? a : b; }
inline int getmax(int a, int b) { return dfn[a] > dfn[b] ? a : b; }

inline int askmin(int l, int r) {
    // if(l > r) swap(l, r);
    int k = lg[r - l + 1];
    return getmin(mn[l][k], mn[r - (1 << k) + 1][k]);
}

inline int askmax(int l, int r) {
    // if(l > r) swap(l, r);
    int k = lg[r - l + 1];
    return getmax(mx[l][k], mx[r - (1 << k) + 1][k]);
}

int ask_root_dep(int u, int v) {
    int l = lca_dfn[u], r = lca_dfn[v];
    if(l > r) swap(l, r);
    int k = lg[r - l + 1];
    return min(tl[l][k], tl[r - (1 << k) + 1][k]); 
}

namespace SEG {
    int mn[SEGN], mx[SEGN], root[N], node_cnt;
    int tag[SEGN], lc[SEGN], rc[SEGN];
    void modify(int x, int l, int r, int pos) {
        int mid = (l + r) >> 1;
        mn[x] = mx[x] = pos;
        if(l == r) {
            return ;
        } else if(pos <= mid) {
            modify(lc[x] = ++ node_cnt, l, mid, pos); 
        } else {
            modify(rc[x] = ++ node_cnt, mid + 1, r, pos);
        }
    }
    void push(int x) {
        if(tag[x]) {
             if(lc[x] && rc[x]) {
                pts[++ pts_cnt] = (P) { mx[lc[x]], mn[rc[x]], tag[x] };
            }
            if(lc[x]) tag[lc[x]] += tag[x];
            if(rc[x]) tag[rc[x]] += tag[x];
            tag[x] = 0;
        }
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        push(x), push(y);
        mn[x] = min(mn[x], mn[y]);
        mx[x] = max(mx[x], mx[y]);
        lc[x] = merge(lc[x], lc[y]);
        rc[x] = merge(rc[x], rc[y]);
        return x;    
    }
    void go(int x) {
        if(!x) return ;
        push(x);
        go(lc[x]), go(rc[x]);
    }
    inline void modify_API(int u, int val) {
        modify(root[u] = ++ node_cnt, 1, VAL_CNT, val);
    }
    inline void merge_API(int u, int v) {
        root[u] = merge(root[u], root[v]);
    }
};

inline void get_pts(int u, int fa) {
    SEG :: modify_API(u, a[u]);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        get_pts(v, u);
        SEG :: merge_API(u, v);
    }
    
    ++ SEG :: tag[SEG :: root[u]];
    pts[++ pts_cnt] = (P) { -inf, SEG :: mn[SEG :: root[u]], 1 };
    pts[++ pts_cnt] = (P) { SEG :: mx[SEG :: root[u]], inf, 1 }; 
}

namespace ERWEISHUDIAN {
    struct ASK { int id, x, y; } ask[Q]; int ask_cnt;
    
    inline bool ASK_cmpy(ASK a, ASK b) { return a.y == b.y ? a.x < b.x : a.y > b.y; } 
    inline bool PTS_cmpy(P a, P b) { return a.y == b.y ? a.x < b.x : a.y > b.y; }
    inline void add(int id, int x, int y) { ask[++ ask_cnt] = (ASK) { id, x, y }; }
    ll bit[BIT];
    inline void ins(int x, int y) {
        for( ; x <= VAL_CNT ; x += x & -x) bit[x] += y;
    }
    inline ll askbit(int x) {
        ll res = 0;
        for( ; x ; x -= x & -x) res += bit[x];
        return res;
    }
    
    inline void sol() {
        int newvalcnt = VAL_CNT + 2;
        for(int i = 1 ; i <= pts_cnt; ++ i) {
            if(pts[i].x == -inf) pts[i].x = 1;
            else ++ pts[i].x;
            if(pts[i].y == inf) pts[i].y = newvalcnt;
            else ++ pts[i].y;
        }
        VAL_CNT = newvalcnt;
        sort(ask + 1, ask + 1 + ask_cnt, ASK_cmpy);
        sort(pts + 1, pts + 1 + pts_cnt, PTS_cmpy);
        for(int i = 1, j = 1 ; i <= ask_cnt ; ++ i) {
            ++ ask[i].x, ++ ask[i].y;
            while(j <= pts_cnt && pts[j].y >= ask[i].y)
                ins(pts[j].x, pts[j].w), ++ j;
            output[ask[i].id] = askbit(ask[i].x);
        }
    }
}

int main() {
    ele[++ ele_cnt] = { -inf, -inf };
    ele[++ ele_cnt] = { inf, inf };
    n = io(), q = io();
    for(int i = 1 ; i <= n ; ++ i) ele[++ ele_cnt] = { a[i] = io(), i };
    for(int i = 1 ; i < n ; ++ i) {
        int u = io(), v = io();
        add(u, v), add(v, u); 
    }
    sort(ele + 1, ele + 1 + ele_cnt);
    ele_cnt = unique(ele + 1, ele + 1 + ele_cnt) - ele - 1;
    VAL_CNT = ele_cnt;
    for(int i = 1 ; i <= n ; ++ i) a[i] = lower_bound(ele + 1, ele + 1 + ele_cnt, make_pair(a[i], i)) - ele;
    dfs(1, 0);
    for(int i = 2 ; i <= max(lca_clk, VAL_CNT) ; ++ i) lg[i] = lg[i >> 1] + 1;
    banmn = VAL_CNT + 1, banmx = VAL_CNT + 2; 
    for(int i = 1 ; i <= VAL_CNT ; ++ i) mn[i][0] = banmn, mx[i][0] = banmx;
    dfn[banmn] = inf, dfn[banmx] = -inf;
    for(int i = 1 ; i <= n ; ++ i) mn[a[i]][0] = i, mx[a[i]][0] = i;
    for(int j = 1 ; j <= 19 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= VAL_CNT ; ++ i)
            mn[i][j] = getmin(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]),
            mx[i][j] = getmax(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        for(int i = 1 ; i + (1 << j) - 1 <= lca_clk ; ++ i)
            tl[i][j] = min(tl[i][j - 1], tl[i + (1 << (j - 1))][j - 1]); 
    }
    get_pts(1, 0);
    SEG :: go(SEG :: root[1]);
    for(int qfa = 1 ; qfa <= q ; ++ qfa) {
        int L = mem[qfa].L = io(), R = mem[qfa].R = io();
        int ql = upper_bound(ele + 1, ele + 1 + ele_cnt, make_pair(L - 1, inf)) - ele - 1;
        int qr = lower_bound(ele + 1, ele + 1 + ele_cnt, make_pair(R + 1, -inf)) - ele;
        if(ql <= qr) ERWEISHUDIAN :: add(qfa, ql, qr);
    }
    ERWEISHUDIAN :: sol();
    for(int qfa = 1 ; qfa <= q ; ++ qfa) {
        int L = mem[qfa].L, R = mem[qfa].R;
        int ql = lower_bound(ele + 1, ele + 1 + ele_cnt,  make_pair(L, -inf)) - ele;
        int qr = upper_bound(ele + 1, ele + 1 + ele_cnt,  make_pair(R, inf)) - ele - 1;
        ll ans = n - output[qfa];
        if(ql <= qr) {
            int amn = askmin(ql, qr), amx = askmax(ql, qr);
            if(amn != banmn && amx != banmx) ans -= ask_root_dep(amn, amx) - 1;
        }
        io(ans);
    }
}
