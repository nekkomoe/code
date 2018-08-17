#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];
int deg[N], val[N], vis[N], n, m;
long long ans;
struct E { int u, v; } e[N * 3];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &val[i]);
	for(int i = 1 ; i <= m ; ++ i) {
		scanf("%d%d", &e[i].u, &e[i].v);
		++ deg[e[i].u], ++ deg[e[i].v];
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int u = e[i].u, v = e[i].v;
		if(deg[u] < deg[v] || (deg[u] == deg[v] && u > v)) swap(u, v);
		g[u].push_back(v);
	}
	for(int x = 1 ; x <= n ; ++ x) {
		for(int i = 0 ; i < g[x].size() ; ++ i) vis[g[x][i]] = x;
		for(int i = 0 ; i < g[x].size() ; ++ i) {
			int y = g[x][i];
			for(int j = 0 ; j < g[y].size() ; ++ j) {
				int z = g[y][j];
				if(vis[z] == x) {
					ans += max(max(val[x], val[y]), val[z]);
				}
			}
		}
	}
	printf("%lld\n", ans);
}
