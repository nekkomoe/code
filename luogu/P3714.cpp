#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, inf = 2e9 + 10;

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
        int c = xchar(), x = 0, f = 0;
		while(!isdigit(c) && c != '-') c = xchar();
		if(c == '-') f = 1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return f ? -x : x;
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

int n, m, L, R;
struct E { int v, w; }; bool operator < (E a, E b) { return a.w < b.w; }
vector<E> G[N];

int f[N] = { inf }, root, size, sz[N], ban[N], c[N], ans = -inf;

void getroot(int u, int fa) {
    f[u] = 0, sz[u] = 1;
    for(E &e: G[u])
        if(!ban[e.v] && e.v != fa)
            getroot(e.v, u),
			sz[u] += sz[e.v],
			f[u] = max(f[u], sz[e.v]);
    f[u] = max(f[u], size - sz[u]);
    if(f[root] > f[u]) root = u;
}

E edge[N];

struct SegTree {
    int mx[N * 4];
    #define lc (id << 1)
    #define rc (id << 1 | 1)
    void clear() { for(int i = 0 ; i < N * 4 ; ++ i) mx[i] = -inf; }
    SegTree() { clear(); }
    void modify(int id, int l, int r, int pos, int val, int ty) { // ty = 1: add, ty = -1: del
        int mid = (l + r) >> 1;
        if(l == r) return mx[id] = ty == 1 ? max(mx[id], val) : -inf, void();
        else if(pos <= mid) modify(lc, l, mid, pos, val, ty);
        else modify(rc, mid + 1, r, pos, val, ty);
        mx[id] = max(mx[lc], mx[rc]);
    }
    int query(int id, int l, int r, int ql, int qr) {
        int mid = (l + r) >> 1;
        if(ql <= l && r <= qr) return mx[id];
        else if(qr <= mid) return query(lc, l, mid, ql, qr);
        else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
        else return max(query(lc, l, mid, ql, mid), query(rc, mid + 1, r, mid + 1, qr));
    }
} glo, loc;

void getglo(int u, int fa, int sum, int lastcol, int dep) {
    if(L <= dep && dep <= R) ans = max(ans, sum);
    int ql = L - dep, qr = R - dep;
    if(qr >= 1) {
        ql = max(ql, 1);
        int t = glo.query(1, 1, n, ql, qr);
        if(t != -inf) ans = max(ans, t + sum);
    }
    for(E &e: G[u])
        if(!ban[e.v] && e.v != fa) {
            if(lastcol == e.w) getglo(e.v, u, sum, e.w, dep + 1);
            else getglo(e.v, u, sum + c[e.w], e.w, dep + 1);
        }
}

void pushglo(int u, int fa, int sum, int lastcol, int dep, int ty) {
    glo.modify(1, 1, n, dep, sum, ty);
    for(E &e: G[u])
        if(!ban[e.v] && e.v != fa) {
            if(lastcol == e.w) pushglo(e.v, u, sum, e.w, dep + 1, ty);
            else pushglo(e.v, u, sum + c[e.w], e.w, dep + 1, ty);
        }
}

void getloc(int u, int fa, int sum, int lastcol, int dep) {
    int ql = L - dep, qr = R - dep;
    if(qr >= 1) {
        ql = max(ql, 1);
        int t = loc.query(1, 1, n, ql, qr);
        if(t != -inf) ans = max(ans, t + sum);
    }
    for(E &e: G[u])
        if(!ban[e.v] && e.v != fa) {
            if(lastcol == e.w) getloc(e.v, u, sum, e.w, dep + 1);
            else getloc(e.v, u, sum + c[e.w], e.w, dep + 1);
        }
}

void pushloc(int u, int fa, int sum, int lastcol, int dep, int ty) {
    loc.modify(1, 1, n, dep, sum, ty);
    for(E &e: G[u])
        if(!ban[e.v] && e.v != fa) {
            if(lastcol == e.w) pushloc(e.v, u, sum, e.w, dep + 1, ty);
            else pushloc(e.v, u, sum + c[e.w], e.w, dep + 1, ty);
        }
}

void sol(int u) {
    ban[u] = 1;
    
    sort(G[u].begin(), G[u].end());

    int p = 0;
    for(E &e: G[u]) 
        if(!ban[e.v])
            edge[++ p] = e;
            
    for(int i = 1, frst = 1 ; i <= p ; ++ i) {

        if(i == p || edge[i].w != edge[i + 1].w) {

        	for(int j = frst ; j <= i ; ++ j) {
        		getglo(edge[j].v, u, c[edge[j].w], edge[j].w, 1);
        	}

        	for(int j = frst ; j <= i ; ++ j) {
        		getloc(edge[j].v, u, 0, edge[j].w, 1);
        		pushloc(edge[j].v, u, c[edge[j].w], edge[j].w, 1, 1);
        	}

            for(int j = frst ; j <= i ; ++ j) {
            	pushloc(edge[j].v, u, c[edge[j].w], edge[j].w, 1, -1);
            }

            for(int j = frst ; j <= i ; ++ j) {
            	pushglo(edge[j].v, u, c[edge[j].w], edge[j].w, 1, 1);
            }
            
            frst = i + 1;
        }
        
    }

    for(int i = 1 ; i <= p ; ++ i) {
    	pushglo(edge[i].v, u, c[edge[i].w], edge[i].w, 1, -1);
    }

    for(E &e: G[u])
        if(!ban[e.v])
            root = 0,
			size = sz[e.v],
			getroot(e.v, 0),
			sol(root);
}

int main() {
    n = io(), m = io(), L = io(), R = io();
    for(int i = 1 ; i <= m ; ++ i) c[i] = io();
    for(int i = 1, u, v, c ; i < n ; ++ i)
        u = io(), v = io(), c = io(),
        G[u].push_back((E) { v, c }),
		G[v].push_back((E) { u, c });
    root = 0, size = n, getroot(1, 0), sol(root);
    printf("%d\n", ans);
}
