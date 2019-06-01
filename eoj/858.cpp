#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;

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

int n;
vector<int> g[N];
vector<int> g_blue[N], g_red[N];
struct E {
    int u, v;
} e_blue[N], e_red[N];
int dfn_blue[N], dfn_red[N];
pair<int, int> ran_blue[N], ran_red[N];
int clk_blue, clk_red;

inline void dfs_blue(int u, int fa) {
    dfn_blue[u] = ++ clk_blue;
    for(int v: g_blue[u]) {
        if(v != fa) {
            dfs_blue(v, u);
        }
    }
    ran_blue[u] = make_pair(dfn_blue[u], clk_blue);
}

inline void dfs_red(int u, int fa) {
    dfn_red[u] = ++ clk_red;
    for(int v: g_red[u]) {
        if(v != fa) {
            dfs_red(v, u);
        }
    }
    ran_red[u] = make_pair(dfn_red[u], clk_red);
}

int vis[2 * N];

inline void chkmin(int &x, int y) {
    x = min(x, y);
}
inline void chkmax(int &x, int y) {
    x = max(x, y);
}

struct P {
    int d[2], mn[2], mx[2];
    int lc, rc, id;
    int subtree_rem;
    inline void setmnmxd() {
        mn[0] = mx[0] = d[0];
        mn[1] = mx[1] = d[1];
    }
} pts_blue[N], pts_red[N];

queue<int> nxt;

int D;
bool cmp(P a, P b) {
    return a.d[D] < b.d[D];
}

struct KDT {
    P *pts;
    int rt;
    int build(int l, int r, int d) {
        D = d;
        int mid = (l + r) >> 1;
        nth_element(pts + l, pts + mid, pts + r + 1, cmp);
        pts[mid].setmnmxd();
        if(l < mid) {
            pts[mid].lc = build(l, mid - 1, !d);
            chkmin(pts[mid].mn[0], pts[pts[mid].lc].mn[0]);
            chkmax(pts[mid].mx[0], pts[pts[mid].lc].mx[0]);
            chkmin(pts[mid].mn[1], pts[pts[mid].lc].mn[1]);
            chkmax(pts[mid].mx[1], pts[pts[mid].lc].mx[1]);
        }
        if(mid < r) {
            pts[mid].rc = build(mid + 1, r, !d);
            chkmin(pts[mid].mn[0], pts[pts[mid].rc].mn[0]);
            chkmax(pts[mid].mx[0], pts[pts[mid].rc].mx[0]);
            chkmin(pts[mid].mn[1], pts[pts[mid].rc].mn[1]);
            chkmax(pts[mid].mx[1], pts[pts[mid].rc].mx[1]);
        }
        return mid;
    }
    inline void init() {
        for(int i = 1 ; i <= n - 1 ; ++ i) {
            if(pts[i].d[0] > pts[i].d[1]) {
                swap(pts[i].d[0], pts[i].d[1]);
            }
        }
        rt = build(1, n - 1, 0);
    }

    inline void ask(int rt, int l, int r, int x, int y) {
        if(!rt || pts[rt].subtree_rem) {
            return ;
        }
        if(r < pts[rt].mn[0] || l > pts[rt].mx[0]
        || y < pts[rt].mn[1] || x > pts[rt].mx[1]) {
            return ;
        }
        if(l <= pts[rt].d[0] && pts[rt].d[0] <= r
        && x <= pts[rt].d[1] && pts[rt].d[1] <= y
        && vis[pts[rt].id] == 0) {
            vis[pts[rt].id] = 1;
            nxt.emplace(pts[rt].id);
        }
        pts[rt].subtree_rem = vis[pts[rt].id];
        if(pts[rt].lc) {
            ask(pts[rt].lc, l, r, x, y);
            pts[rt].subtree_rem &= pts[pts[rt].lc].subtree_rem;
        }
        if(pts[rt].rc) {
            ask(pts[rt].rc, l, r, x, y);
            pts[rt].subtree_rem &= pts[pts[rt].rc].subtree_rem;
        }
    }

    inline void ask_api(int idx) {
        int u, v, l, r;
        if(idx <= n - 1) {
            u = e_blue[idx].u, v = e_blue[idx].v;
            l = max(ran_blue[u].first, ran_blue[v].first);
            r = min(ran_blue[u].second, ran_blue[v].second);
        } else {
            u = e_red[idx - (n - 1)].u, v = e_red[idx - (n - 1)].v;
            l = max(ran_red[u].first, ran_red[v].first);
            r = min(ran_red[u].second, ran_red[v].second);
        }
        if(1 <= l - 1) {
            // ask(rt, l, r, 1, l - 1);
            ask(rt, 1, l - 1, l, r);
        }
        if(r + 1 <= n) {
            ask(rt, l, r, r + 1, n);
            // ask(rt, r + 1, n, l, r);
        }
    }

} KDT_blue, KDT_red;



int main() {

    // freopen("two.in", "r", stdin);
    // freopen("two.out", "w", stdout);

    n = io();
    for(int i = 2, fa ; i <= n ; ++ i) {
        fa = io();
        e_blue[i - 1] = (E) { fa, i };
        g_blue[i].push_back(fa);
        g_blue[fa].push_back(i);
    }
    for(int i = 2, fa ; i <= n ; ++ i) {
        fa = io();
        e_red[i - 1] = (E) { fa, i };
        g_red[i].push_back(fa);
        g_red[fa].push_back(i);
    }
    dfs_blue(1, 0);
    dfs_red(1, 0);

    for(int i = 1 ; i <= n - 1 ; ++ i) {
        int u = e_blue[i].u, v = e_blue[i].v;
        pts_blue[i].d[0] = dfn_red[u];
        pts_blue[i].d[1] = dfn_red[v];
        pts_blue[i].id = i;
    }
    KDT_blue.pts = pts_blue;
    KDT_blue.init();
    
    for(int i = 1 ; i <= n - 1 ; ++ i) {
        int u = e_red[i].u, v = e_red[i].v;
        pts_red[i].d[0] = dfn_blue[u];
        pts_red[i].d[1] = dfn_blue[v];
        pts_red[i].id = (n - 1) + i;
    }
    KDT_red.pts = pts_red;
    KDT_red.init();

    int idx = io();
    queue<int> q;
    vis[idx] = 1, q.emplace(idx);
    while(q.size()) {
        nxt = queue<int> ();
        int isblue = q.front() <= n - 1;
        puts(isblue ? "Blue" : "Red");
        vector<int> res;
        while(q.size()) {
            int idx = q.front(); q.pop();
            res.push_back(idx);
            if(isblue) {
                KDT_red.ask_api(idx);
            } else {
                KDT_blue.ask_api(idx);
            }
        }
        sort(res.begin(), res.end());
        for(int i = 0 ; i < res.size() ; ++ i) {
            if(i) putchar(' ');
            int x = res[i];
            printf("%d", x >= n ? x - (n - 1) : x);
        }
        puts("");
        q = nxt;
    }
}
