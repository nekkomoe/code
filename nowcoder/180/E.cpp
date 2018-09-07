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
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

const int mod = 1e9 + 7, N = 1e5 + 10;

int n, m, a[N];
vector<int> g[N];

int fa[N], top[N], dep[N], sz[N], son[N], pos[N], dfn[N], clk;

void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	sz[u] = 1;
	for(int v: g[u])
		if(v != fa[u]) {
			fa[v] = u, dfs(v), sz[u] += sz[v];
			if(sz[v] > sz[son[u]]) son[u] = v;
		}
}

void dfs(int u, int tp) {
	top[u] = tp;
	dfn[u] = ++ clk, pos[clk] = u;
	if(son[u]) dfs(son[u], tp);
	for(int v: g[u])
		if(v != fa[u] && v != son[u])
			dfs(v, v);
}

ll sum[N * 10], sqrsum[N * 10], tag[N * 10];

#define lc (id << 1)
#define rc (id << 1 | 1)

void push(int id, int l, int r) {
	if(tag[id]) {
		(tag[lc] += tag[id]) %= mod, (tag[rc] += tag[id]) %= mod;
		ll x = tag[id];
		sqrsum[id] = ((sqrsum[id] + x * x * (r - l + 1) % mod) % mod + 2 * x * sum[id]) % mod;
		sum[id] = (sum[id] + x * (r - l + 1) % mod) % mod;
		tag[id] = 0;
	}
}

void update(int id, int l, int r) {
	int mid = (l + r) >> 1;
	push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
	sum[id] = sum[lc] + sum[rc];
	sqrsum[id] = sqrsum[lc] + sqrsum[rc];
}

void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) {
		ll x = a[pos[l]];
		sum[id] = x % mod;
		sqrsum[id] = x * x % mod;
	} else {
		build(lc, l, mid), build(rc, mid + 1, r);
		update(id, l, r);
	}
}

void modify(int id, int l, int r, int ql, int qr, ll x) {
	int mid = (l + r) >> 1;
	push(id, l, r);
	if(ql <= l && r <= qr) {
		tag[id] += x;
		return ;
	} else if(qr <= mid) {
		modify(lc, l, mid, ql, qr, x);
	} else if(ql >= mid + 1) {
		modify(rc, mid + 1, r, ql, qr, x);
	} else {
		modify(lc, l, mid, ql, mid, x);
		modify(rc, mid + 1, r, mid + 1, qr, x);
	}
	update(id, l, r);
}

pair<ll, ll> query(int id, int l, int r, int ql, int qr) {
	int mid = (l + r) >> 1;
	push(id, l, r);
	if(ql <= l && r <= qr) {
		return make_pair(sum[id], sqrsum[id]);
	} else if(qr <= mid) {
		return query(lc, l, mid, ql, qr);
	} else if(ql >= mid + 1) {
		return query(rc, mid + 1, r, ql, qr);
	} else {
		pair<ll, ll> lef = query(lc, l, mid, ql, mid),
					 rig = query(rc, mid + 1, r, mid + 1, qr);
		return make_pair((lef.first + rig.first) % mod, (lef.second + rig.second) % mod);
	}
}

void modify(int u, int v, ll x) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		modify(1, 1, n, dfn[top[u]], dfn[u], x);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	modify(1, 1, n, dfn[u], dfn[v], x);
}

const ll inv2 = 500000004;

ll query(int u, int v) {
	ll sum = 0, sqrsum = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		pair<ll, ll> res = query(1, 1, n, dfn[top[u]], dfn[u]);
		sum = (sum + res.first) % mod;
		sqrsum = (sqrsum + res.second) % mod;
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	pair<ll, ll> res = query(1, 1, n, dfn[u], dfn[v]);
	sum = (sum + res.first) % mod;
	sqrsum = (sqrsum + res.second) % mod;
	return ((sum * sum) % mod - sqrsum) % mod * inv2 % mod;
}

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
	return r;
}

int main() {
//	freopen("data.in", "r", stdin);
	n = io(), m = io();
	for(int i = 1 ; i <= n ; ++ i) a[i] = io();
	for(int i = 1, u, v ; i < n ; ++ i) {
		u = io(), v = io();
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1), dfs(1, 1), build(1, 1, n);
	for(int i = 1, op, u, v, val ; i <= m ; ++ i) {
		op = io();
//		printf("in: %d \n", i);
		if(op == 1) {
			u = io(), val = io();
			modify(1, 1, n, dfn[u], dfn[u] + sz[u] - 1, val);
		} else if(op == 2) {
			u = io(), v = io(), val = io();
			modify(u, v, val);
		} else if(op == 3) {
			u = io(), v = io();
			ll ans = query(u, v);
			printf("%lld\n", (ans % mod + mod) % mod);
		}
	}
}
