#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
vector<int> g[N]; int n, sz[N], len[N]; char s[N];
ll f[N], d[N], ans;
void dfs(int u) {
	if(g[u].empty())
		sz[u] = 1,
		ans = (f[1] += (-- d[u]));
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		d[v] = d[u] + len[v] + 1,
		dfs(v),
		sz[u] += sz[v];
	}
}
void dfs(int u, int fa) {
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(g[v].size()) {
			ans = min(ans,
				f[v] = f[u] - (len[v] + 1) * sz[v] + (sz[1] - sz[v]) * 3);
			dfs(v, u);
		}
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1, m ; i <= n ; ++ i) {
		scanf("%s%d", s, &m), len[i] = strlen(s);
		for(int j = 1, x ; j <= m ; ++ j)
			scanf("%d", &x),
			g[i].push_back(x);
	}
	dfs(1), dfs(1, 0);
	printf("%lld\n", ans);
}
