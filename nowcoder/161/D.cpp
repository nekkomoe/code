#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
vector<int> g[N], col[N];
int tot, n, q, c[N], dep[N], fa[N][21];
map<int, int> tr;

int get(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

void dfs(int u) {
	dep[u] = dep[fa[u][0]] + 1;
	for(int i = 1 ; i <= 20 ; ++ i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	col[tr[c[u]]].push_back(u);
	for(int v: g[u])
		if(v != fa[u][0])
			fa[v][0] = u,
			dfs(v);
}

int dis(int u, int v) {
	return dep[u] + dep[v] - 2 * dep[get(u, v)];
}

int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> q;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> c[i];
		if(tr.find(c[i]) == tr.end()) tr[c[i]] = ++ tot;
	}
	for(int i = 1, u, v ; i < n ; ++ i)
		cin >> u >> v,
		g[u].push_back(v),
		g[v].push_back(u);
	dfs(1);
	for(int i = 1 ; i <= tot ; ++ i) {
		int p1 = 0, p2 = 0, d = 0;
		for(int u: col[i]) {
			if(!p1) p1 = u;
			else if(!p2) p2 = u, d = get(p1, p2);
			else {
				pair<int, pair<int, int> > p[3] = {
					{ dis(p1, p2), { p1, p2 } },
					{ dis(p1, u), { p1, u } },
					{ dis(p2, u), { p2, u } }
				};
				auto t = *max_element(p, p + 3);
				d = t.first, p1 = t.second.first, p2 = t.second.second;
			}
		}
		col[i].clear(); col[i].push_back(p1);
		if(p2) col[i].push_back(p2);
	}
	for(int i = 1, c1, c2 ; i <= q ; ++ i) {
		cin >> c1 >> c2;
		c1 = tr[c1], c2 = tr[c2];
		int ans = 0;
		for(int u: col[c1])
			for(int v: col[c2])
				ans = max(ans, dis(u, v));
		cout << ans << endl;
	}
}
