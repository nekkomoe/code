// luogu-judger-enable-o2
%:pragma GCC optimize(2)

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
    int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
const int N = 1e5 + 10, inf = 0x3f3f3f3f, neinf = 0x3f3f3f3f;
int n, L, R, flag;
struct E { int v; double w; int _w; };
vector<E> g[N];
int sz[N], f[N] = { inf }, root, size, ban[N];

void getrt(int u, int fa) {
    f[u] = 0, sz[u] = 1;
    for(int i = 0 ; i < g[u].size() ; ++ i) { 
    	E &e = g[u][i]; 
        int &v = e.v;
        if(!ban[v] && v != fa)
            getrt(v, u),
            sz[u] += sz[v],
            f[u] = max(f[u], sz[v]);
    }
    f[u] = max(f[u], size - sz[u]);
    if(f[u] < f[root]) root = u;
}

int mxdep[N], que[N];
double d[N], glo[N];

inline bool cmp(E a, E b) { return mxdep[a.v] < mxdep[b.v]; }

vector<pair<int, int> > mem[N]; int Q;

int getdep(int u, int fa, int d) {
    mxdep[u] = d;
    for(int i = 0 ; i < g[u].size() ; ++ i) { 
    	E &e = g[u][i]; 
        int v = e.v;
        if(!ban[v] && v != fa)
            mxdep[u] = max(mxdep[u], getdep(v, u, d + 1));
    }
    mem[Q].push_back(make_pair(u, mxdep[u]));
    return mxdep[u];
}

vector<int> nxt[N];

int thesz[N];

void build(int u) {
	thesz[u] = size,
	ban[u] = 1,
	Q = u,
	getdep(u, 0, 0),
    sort(g[u].begin(), g[u].end(), cmp);
    for(int i = 0 ; i < g[u].size() ; ++ i) { 
    	E &e = g[u][i]; 
        int v = e.v;
        if(!ban[v])
            root = 0,
            size = sz[v],
            getrt(v, u),
            nxt[u].push_back(root),
			build(root);
    }
}

void dfs(int u, int fa, int dep, double val) {
    d[dep] = max(d[dep], val);
    for(int i = 0 ; i < g[u].size() ; ++ i) { 
        E &e = g[u][i]; 
        int &v = e.v;
        if(!ban[v] && v != fa)
            dfs(v, u, dep + 1, val + e.w);
    }
}


void sol(int u) {
	if(thesz[u] <= L || flag) return ;
    
    ban[u] = 1;
    for(int i = mem[u].back().second ; i ; -- i) glo[i] = -1e18;
    for(int i = 0 ; i < mem[u].size() ; ++ i)
    	mxdep[mem[u][i].first] = mem[u][i].second;
    
    for(int i = 0, len = 0 ; i < g[u].size() ; ++ i) { 
        E &e = g[u][i]; 
        int &v = e.v;
        if(!ban[v]) {
            for(int i = 1 ; i <= mxdep[v] ; ++ i) d[i] = -1e18;
            dfs(v, u, 1, e.w);
            int ql = 1, qr = 0, j = 0;
            for(int i = mxdep[v] ; i ; -- i) {
                int l = max(1, L - i), r = R - i, t = min(r, len);
                if(L <= i && i <= R && d[i] >= 0) return flag = 1, void();
                else if(l <= r) {
                    while(j + 1 <= t) {
                        ++ j;
						while(ql <= qr && glo[que[qr]] < glo[j]) -- qr;
                        que[++ qr] = j;
                    }
                    
                    while(ql <= qr && que[ql] < l) ++ ql;
                    if(ql <= qr && d[i] + glo[que[ql]] >= 0)
                        return flag = 1, void();
                }
            }
            for(int i = 1 ; i <= mxdep[v] ; ++ i) glo[i] = max(glo[i], d[i]);
			len = mxdep[v];
        }
    }
    
    for(int i = 0 ; i < nxt[u].size() ; ++ i) sol(nxt[u][i]);
}

int gloroot = 0;

bool check(double T) {
    for(int u = 1 ; u <= n ; ++ u) {
        ban[u] = 0;
        for(int i = 0 ; i < g[u].size() ; ++ i) { 
        	E &e = g[u][i]; 
            e.w = e._w - T;
        }
    }
	flag = 0, sol(gloroot);
    return flag;
}

int main() {
//	freopen("data.in", "r", stdin);
    n = io(), L = io(), R = io();
    double l = 1e6, r = 1e6, ans;
    for(int i = 1, u, v, w ; i < n ; ++ i)
        u = io(), v = io(), w = io(),
        l = min(l, (double) w), 
        g[u].push_back((E) { v, 0, w }), g[v].push_back((E) { u, 0, w });
    root = 0, size = n, getrt(1, 0), build(gloroot = root);
    for(int i = 35 ; i ; -- i) {
        double mid = (l + r) / 2;
        if(check(mid)) ans = mid, l = mid;
        else r = mid;
    }
    printf("%.3lf\n", ans);
}
