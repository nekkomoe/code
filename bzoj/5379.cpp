#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
typedef long long ll;

int n, q, w[N];

int head[N], rest[N * 2], to[N * 2], tot;

int pos[N], l[N], r[N]; ll val[N];

void add(int u, int v) {
	to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int root;

ll c1[N], c2[N];

void bt_add(int x, ll y) {
	for(int i = x ; i <= n ; i += i & -i) c1[i] += y, c2[i] += x * y;
}

ll bt_query(int x) {
	ll res = 0;
	for(int i = x ; i ; i -= i & -i) res += (x + 1) * c1[i] - c2[i];
	return res;
}

inline void modify(int l, int r, ll x) {
	bt_add(l, x), bt_add(r + 1, -x);
}

inline ll query(int l, int r) {
	ll suml = val[l - 1] + bt_query(l - 1);
	ll sumr = val[r] + bt_query(r);
	return sumr - suml;
}

int fa[N][21], dep[N], clk;

inline int gettruelca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 18 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 18 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

inline bool inroot(int u) {
	return l[root] <= pos[u] && pos[u] <= r[root];
}

int getlca(int u, int v) {
	int lca1 = gettruelca(root, u);
	int lca2 = gettruelca(root, v);
	if(lca1 == lca2) return gettruelca(u, v);
	else return dep[lca1] > dep[lca2] ? lca1 : lca2;
}

void dfs(int u) {
	l[u] = pos[u] = ++ clk;
	val[clk] = w[u];
	dep[u] = dep[fa[u][0]] + 1;
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == fa[u][0]) continue;
		fa[v][0] = u;
		dfs(v);
	}
	r[u] = clk;
}

int getson(int gra) {
	int u = root;
	for(int i = 18 ; ~ i ; -- i) if(dep[fa[u][i]] > dep[gra]) u = fa[u][i];
	return u;
}

void modify(int u, int x) {
	if(inroot(u)) {
		if(u != root) modify(l[u], r[u], x);
		else modify(1, n, x);
	} else {
		int p = getson(u);
		if(fa[p][0] == u) {
			modify(1, n, x), modify(l[p], r[p], -x);
		} else {
			modify(l[u], r[u], x);
		}
	}
}

ll query(int u) {
	if(inroot(u)) {
		if(u != root)  return query(l[u], r[u]);
		else return query(1, n);
	} else {
		int p = getson(u);
		if(fa[p][0] == u) {
			return query(1, n) - query(l[p], r[p]);
		} else {
			return query(l[u], r[u]);
		}
	}
}

int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &w[i]);
	for(int i = 1, u, v ; i < n ; ++ i) {
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	
	root = 1;
	dfs(1);
	for(int j = 1 ; j <= 18 ; ++ j)
		for(int i = 1 ; i <= n ; ++ i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	for(int i = 1 ; i <= n ; ++ i) val[i] += val[i - 1];
	
	for(int i = 1, op, u, v, x ; i <= q ; ++ i) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d", &root);
		} else if(op == 2) {
			scanf("%d%d%d", &u, &v, &x);
			modify(getlca(u, v), x);
		} else if(op == 3) {
			scanf("%d", &u);
			printf("%lld\n", query(u));
		}
	}
}
