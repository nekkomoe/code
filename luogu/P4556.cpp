#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, T = 70;
int n, m, fa[N][21], dep[N];
vector<int> g[N];
void getdep(int u) {
	dep[u] = dep[fa[u][0]] + 1;
	for(int i = 1 ; i <= 20 ; ++ i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(int v: g[u])
		if(v != fa[u][0])
			fa[v][0] = u,
			getdep(v);
}
int getlca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int lc[N * T], rc[N * T], sum[N * T], id[N * T], tot;

void up(int x) {
	id[x] = sum[lc[x]] >= sum[rc[x]] ? id[lc[x]] : id[rc[x]];
	sum[x] = max(sum[lc[x]], sum[rc[x]]);
}

void merge(int &x, int y, int l, int r) {
	if(!y) return ;
	else if(!x) x = y;
	else if(l == r) {
		sum[x] += sum[y];
		if(sum[x] == sum[y]) id[x] = l;
	} else {
		int mid = (l + r) >> 1;
		merge(lc[x], lc[y], l, mid);
		merge(rc[x], rc[y], mid + 1, r);
		up(x);
	}
}

void ins(int &x, int l, int r, int pos, int val) {
	int mid = (l + r) >> 1;
	if(!x) x = ++ tot;
	if(l == r) {
		sum[x] += val;
		id[x] = sum[x] ? l : 0;
	} else if(pos <= mid) {
		ins(lc[x], l, mid, pos, val);
		up(x);
	} else {
		ins(rc[x], mid + 1, r, pos, val);
		up(x);
	}
}

int ans[N], root[N];

void dfs(int u) {
	for(int v: g[u])
		if(v != fa[u][0])
			dfs(v),
			merge(root[u], root[v], 1, 100000);
	ans[u] = id[root[u]];
}

int main() {
//	freopen("data.in", "r", stdin);
	cin >> n >> m;
	for(int i = 1, u, v ; i < n ; ++ i)
		cin >> u >> v,
		g[u].push_back(v),
		g[v].push_back(u);
	getdep(1);
	for(int i = 1, u, v, z, d ; i <= m ; ++ i)
		cin >> u >> v >> z,
		d = getlca(u, v),
		ins(root[u], 1, 100000, z, 1),
		ins(root[v], 1, 100000, z, 1),
		ins(root[d], 1, 100000, z, -1),
		ins(root[fa[d][0]], 1, 100000, z, -1);
	dfs(1);
	for(int i = 1 ; i <= n ; ++ i)
		cout << ans[i] << endl;
}
