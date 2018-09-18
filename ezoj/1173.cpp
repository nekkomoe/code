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

int mx[N * 4];

#define lc (id << 1)
#define rc (id << 1 | 1)

void modify(int id, int l, int r, int pos, int val, int force = 0) {
	int mid = (l + r) >> 1;
	if(l == r) return mx[id] = force ? val : max(mx[id], val), void();
	else if(pos <= mid) modify(lc, l, mid, pos, val, force);
	else if(pos >= mid + 1) modify(rc, mid + 1, r, pos, val, force);
	mx[id] = max(mx[lc], mx[rc]);
}

int query(int id, int l, int r, int ql, int qr) {
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) return mx[id];
	else if(qr <= mid) return query(lc, l, mid, ql, qr);
	else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
	else return max(query(lc, l, mid, ql, mid), query(rc, mid + 1, r, mid + 1, qr)); 
}

void dfs(int u, int fa, int ty, int sum, int len) {
	if(ty == 0) {
		if(!flag) {
			if(sum >= 0 && L <= len && len <= R) flag = 1;
			else {
				int l = max(1, L - len), r = R - len;
				if(l <= r && sum + query(1, 1, n, l, r) >= 0) flag = 1;
			}
		}
	} else if(ty == 1) modify(1, 1, n, len, sum);
	else modify(1, 1, n, len, neinf, 1);
	for(E e: g[u]) {
		int v = e.v;
		if(v != fa && !ban[v])
			dfs(v, u, ty, sum + e.w, len + 1);
	}
}

void sol(int u) {
	if(flag) return ;
	ban[u] = 1;
	for(E e: g[u]) {
		int v = e.v;
		if(!ban[v])
			dfs(v, u, 0, e.w, 1),
			dfs(v, u, 1, e.w, 1);
	}
	for(E e: g[u]) {
		int v = e.v;
		if(!ban[v])
			dfs(v, u, -1, e.w, 1);
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

int main() {
	memset(mx, 0xcf, sizeof mx);
	n = io(), L = io(), R = io();
	for(int i = 1, u, v, w ; i < n ; ++ i)
		u = io(), v = io(), w = io(),
		g[u].push_back((E) { v, 0, w }),
		g[v].push_back((E) { u, 0, w }),
		num[++ num[0]] = w;
	sort(num + 1, num + 1 + num[0]);
	num[0] = unique(num + 1, num + 1 + num[0]) - num - 1;
	int l = 1, r = num[0], ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(num[mid])) ans = num[mid], l = mid + 1;
		else r = mid - 1;
	}
	cout << ans << endl;
}
