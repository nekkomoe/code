#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef int ll;

int n, m;
const int N = 70000;
priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
int vis[2 * N + 10];
ll ans[N + 10];
struct P {
    int d[2], mn[2], mx[2], ch[2], id;
} p[N + 10];
struct T {
    int t, xl, xr, yl, yr;
    T(int t = 0, int xl = 0, int xr = 0, int yl = 0, int yr = 0) : t(t), xl(xl), xr(xr), yl(yl), yr(yr) { }
};

vector<T> tmp[N + 10];
ll dis[2 * N + 10];
int t, xl, xr, yl, yr, u;
struct FastIO {
    #define S int(2e7)
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
    #undef S
} io;

inline void chkmin(int &x, int y) {
    x = min(x, y);
}
inline void chkmax(int &x, int y) {
    x = max(x, y);
}

inline void upd(int x) {
    for(int t = 0 ; t < 2 ; ++ t) {
        p[x].mn[t] = p[x].mx[t] = p[x].d[t];
        for(int j = 0 ; j < 2 ; ++ j) {
            int y = p[x].ch[j];
            if(y) {
                chkmin(p[x].mn[t], p[y].mn[t]);
                chkmax(p[x].mx[t], p[y].mx[t]);
            }
        }
    }
}

inline int build(int l, int r, int d) {
    if(l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    nth_element(p + l, p + mid, p + r + 1, [&] (P a, P b) {
        return a.d[d] < b.d[d];
    });
    if(l <= mid - 1) {
        p[mid].ch[0] = build(l, mid - 1, !d);
    }
    if(mid + 1 <= r) {
        p[mid].ch[1] = build(mid + 1, r, !d);
    }
    upd(mid);
    return mid;
}

inline void ask(int x) {
    if(!x
    || p[x].mx[0] < xl || p[x].mn[0] > xr
    || p[x].mx[1] < yl || p[x].mn[1] > yr) {
        return ;
    }
    if(xl <= p[x].mn[0] && p[x].mx[0] <= xr
    && yl <= p[x].mn[1] && p[x].mx[1] <= yr) {
        int v = x;
        if(dis[v] > dis[u] + t) {
            dis[v] = dis[u] + t;
            if(!vis[v]) {
                pq.emplace(dis[v], v);
            }
        }
        return ;
    }
    if(xl <= p[x].d[0] && p[x].d[0] <= xr
    && yl <= p[x].d[1] && p[x].d[1] <= yr) {
        int v = x + n;
        if(dis[v] > dis[u] + t) {
            dis[v] = dis[u] + t;
            if(!vis[v]) {
                pq.emplace(dis[v], v);
            }
        }
    }
    ask(p[x].ch[0]), ask(p[x].ch[1]);
}

int main() {
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);

    // ----------------------------------------BEGIN---------------------------------------

    int w, h;
    n = io(), m = io(), w = io(), h = io();
    p[0].mn[0] = p[0].mn[1] = 1e9;
    p[0].mx[0] = p[0].mx[1] = -1e9;
    int inf = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        p[i].d[0] = io(), p[i].d[1] = io(), p[i].id = i;
        p[i].mn[0] = p[i].mx[0] = p[i].d[0];
        p[i].mn[1] = p[i].mx[1] = p[i].d[1];
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int pid = io(), t = io(), xl = io(), xr = io(), yl = io(), yr = io();
        tmp[pid].emplace_back(t, xl, xr, yl, yr);
        inf += t;
    }
    for(int i = 1 ; i <= 2 * n ; ++ i) {
        dis[i] = inf;
    }

    int rt = build(1, n, 1);
    for(int i = 1 ; i <= n ; ++ i) {
        if(p[i].id == 1) {
            pq.emplace(dis[i + n] = 0, i + n);
            break;
        }
    }
    while(pq.size()) {
        int u = pq.top().second; pq.pop();
        if(vis[u]) {
            continue;
        }
        vis[u] = 1;
        if(u <= n) {
            for(int i = 0 ; i < 2 ; ++ i) {
                int v = p[u].ch[i];
                if(v && dis[v] > dis[u]) {
                    dis[v] = dis[u];
                    if(!vis[v]) {
                        pq.emplace(dis[v], v);
                    }
                }
            }
            int v = u + n;
            if(dis[v] > dis[u]) {
                dis[v] = dis[u];
                if(!vis[v]) {
                    pq.emplace(dis[v], v);
                }
            }
        } else {
            for(const auto &ttt : tmp[p[u - n].id]) {
                :: u = u;
                t = ttt.t, xl = ttt.xl, xr = ttt.xr, yl = ttt.yl, yr = ttt.yr;
                ask(rt);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        ans[p[i].id] = dis[i + n];
    }
    for(int i = 2 ; i <= n ; ++ i) {
        io(ans[i]);
    }

    // -----------------------------------------END----------------------------------------

    return 0;
}
