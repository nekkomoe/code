#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300000 + 10;

int n, m, f[N], deg[N], ans[N], ove[N];

ll h[N], a[N], v[N];

typedef pair<int, int> p;

ll tag_add[N], tag_mul[N], val[N]; int dis[N], lc[N], rc[N];

void ch(int x, ll a, ll b) {
	if(x) {
		val[x] = (val[x] * a + b);
		tag_mul[x] *= a;
		tag_add[x] = (tag_add[x] * a + b);
	}
}

void push(int x) {
	ch(lc[x], tag_mul[x], tag_add[x]);
	ch(rc[x], tag_mul[x], tag_add[x]);
	tag_mul[x] = 1, tag_add[x] = 0;
}

int merge(int x, int y) {
	if(!x || !y) return x | y;
	push(x), push(y);
	if(val[x] > val[y]) swap(x, y);
	rc[x] = merge(rc[x], y);
	if(dis[lc[x]] < dis[rc[x]]) swap(lc[x], rc[x]);
	dis[x] = dis[rc[x]] + 1;
	return x;
}

int root[N], len[N], c[N], dep[N];

vector<int> g[N];

void dfs(int u) {
	dep[u] = dep[f[u]] + 1;
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		dfs(v);
		root[u] = merge(root[u], root[v]);
	}
//	cout << root[u] << " " << val[root[u]] << " " << h[u] << endl;
	while(root[u] && val[root[u]] < h[u]) {
		push(root[u]);
		++ ans[u];
		ove[root[u]] = dep[c[root[u]]] - dep[u];
		root[u] = merge(lc[root[u]], rc[root[u]]);
	}
	if(a[u] == 0) {
		ch(root[u], 1, v[u]);
	} else {
		ch(root[u], v[u], 0);
	}
}

int main() {
//	freopen("data.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i)
		scanf("%lld", &h[i]);
	for(int i = 2 ; i <= n ; ++ i) {
		scanf("%d%lld%lld", &f[i], &a[i], &v[i]),
		g[f[i]].push_back(i);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int s, c;
		scanf("%d%d", &s, &c);
		:: c[i] = c;
		:: val[i] = s;
		tag_mul[i] = 1;
		root[c] = merge(root[c], i);
//		cout << "c = " << c << " root = " << root[c] << endl;
	}
	dfs(1);
	while(root[1])
		push(root[1]),
		ove[root[1]] = dep[c[root[1]]],
		root[1] = merge(lc[root[1]], rc[root[1]]);
	for(int i = 1 ; i <= n ; ++ i) printf("%d\n", ans[i]);
	for(int i = 1 ; i <= m ; ++ i) printf("%d\n", ove[i]);
}
