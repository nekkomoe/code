#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, inf = 0x3f3f3f3f, neinf = 0xcfcfcfcf;

struct E { int v, w, _w; };
vector<E> g[N]; int n, L, R, num[N];

int root, f[N] = { inf }, sz[N], size, ban[N], flag;

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

void getsz(int u, int fa) {
	f[u] = 0, sz[u] = 1;
	for(E e: g[u]) {
		int v = e.v;
		if(v != fa && !ban[v])
			getsz(v, u),
			sz[u] += sz[v],
			f[u] = max(f[u], sz[v]);
	}
	f[u] = max(f[u], size - sz[u]);
	if(f[u] < f[root]) root = u;
}

int U, mxdep[N], d[N], bak[N], id[N];

int getmxdep(int u, int fa, int dep) {
	int mxdep = dep;
	d[dep] = neinf;
	for(E e: g[u])
		if(!ban[e.v] && e.v != fa)
			mxdep = max(mxdep, getmxdep(e.v, u, dep + 1));
	:: mxdep[u] = mxdep;
	return mxdep;
}

bool cmp(E a, E b) { return mxdep[a.v] < mxdep[b.v]; } 
struct T { int v, len, val; };
int que[N], ql, qr;

void ask(int u, int fa, int len, int val) {
	if(val > bak[len]) bak[len] = val, id[len] = u;
	for(E e: g[u]) {
		int v = e.v;
		if(!ban[v] && v != fa)
			ask(v, u, len + 1, val + e.w);
	}
}

void sol(int u) {
	if(flag) return ;
	ban[u] = 1;
	getmxdep(u, 0, 0);
	sort(g[u].begin(), g[u].end(), cmp);
	for(E e: g[u]) {
		int v = e.v;
		if(!ban[v]) {
			for(int i = 0 ; i <= mxdep[v] ; ++ i) bak[i] = neinf;
			ask(v, u, 1, e.w);
			ql = 1, qr = 0; int j = 0;
			for(int i = mxdep[v] ; i ; -- i) {
				int l = max(1, L - i), r = R - i;
				if(L <= i && i <= R && bak[i] >= 0) return U = id[i], flag = 1, void();
				if(l <= r) {
					while(j + 1 <= min(r, mxdep[v])) {
						++ j;
						while(ql <= qr && d[j] >= d[que[qr]]) -- qr;
						que[++ qr] = j;
					}
					while(ql <= qr && que[ql] < l) ++ ql;
					if(ql <= qr && bak[i] + d[que[ql]] >= 0) return U = id[i], flag = 1, void();
				} 
			}
			for(int i = 1 ; i <= mxdep[v] ; ++ i) d[i] = max(d[i], bak[i]);
		}
	}
	
	for(E e: g[u]) {
		int v = e.v;
		if(!ban[v])
			root = 0,
			size = sz[v],
			getsz(v, u),
			sol(root);
	}
}

bool check(int x) {
	for(int u = 1 ; u <= n ; ++ u) {
		ban[u] = 0;
		for(E &e: g[u])
			e.w = e._w >= x ? 1 : -1;
	}
	flag = 0, size = n, root = 0, getsz(1, 0), sol(root);
	return flag;
}

void get(int u, int fa = 0, int sum = 0, int dep = 0) {
	if(L <= dep && dep <= R && sum >= 0) printf("%d\n", u), exit(0); 
	for(E e: g[u]) {
		int v = e.v;
		if(v != fa)
			get(v, u, sum + e.w, dep + 1);
	}
}

int main() {
	n = io(), L = io(), R = io();
	for(int i = 1, u, v, w ; i < n ; ++ i)
		u = io(), v = io(), w = io(),
		g[u].push_back((E) { v, 0, w }),
		g[v].push_back((E) { u, 0, w }),
		num[++ num[0]] = w;
	sort(num + 1, num + 1 + num[0]);
	num[0] = unique(num + 1, num + 1 + num[0]) - num - 1;	
	int l = 1, r = num[0], ans = 0, u = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(num[mid])) ans = num[mid], u = U, l = mid + 1;
		else r = mid - 1;
	}
	for(int u = 1 ; u <= n ; ++ u)
		for(E &e: g[u])
			e.w = e._w >= ans ? 1 : -1;
	printf("%d ", u); get(u);
}
