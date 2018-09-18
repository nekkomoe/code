#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50000 + 10;
int head[N], rest[N * 2], to[N * 2], tot, tag[N], ans, fa[N][21], dep[N], n, m;
void add(int u, int v) {
	to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	:: fa[u][0] = fa;
	for(int i = 1 ; i <= 20 ; ++ i)
		:: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
	for(int i = head[u] ; i ; i = rest[i])
		if(to[i] != fa)
			:: fa[to[i]][0] = u,
			dfs(to[i], u);
}
void re(int u) {
	for(int i = head[u] ; i ; i = rest[i])
		if(to[i] != fa[u][0])
			re(to[i]),
			tag[u] += tag[to[i]];
	ans = max(ans, tag[u]);
}
int get(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v ; i < n ; ++ i)
		scanf("%d%d", &u, &v),
		add(u, v),
		add(v, u);
	dfs(1, 0);
	for(int i = 1, u, v ; i <= m ; ++ i)
		scanf("%d%d", &u, &v),
		++ tag[u],
		++ tag[v],
		-- tag[get(u, v)],
		-- tag[fa[get(u, v)][0]];
	re(1);
	printf("%d\n", ans); 
}
