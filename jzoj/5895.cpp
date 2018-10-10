#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, mod = 998244353;
int n, m, fa[N];
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
int head[N], rest[N * 2], to[N * 2], w[N * 2], tot;
void add(int u, int v, int w) {
	to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}
int deg[N]; long long ans;

void dfs(int u, int fa) {
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		deg[u] += deg[v];
		if(deg[v] & 1) ans = (ans + w[i]) % mod;
	}
}

int main() {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) fa[i] = i;
	for(int i = 1, u, v, w = 1 ; i <= m ; ++ i) {
		scanf("%d%d", &u, &v);
		w = 2ll * w % mod;
		ans = (ans + w) % mod;
		++ deg[u], ++ deg[v];
		if(get(u) == get(v)) continue;
		fa[get(u)] = get(v);
		add(u, v, w), add(v, u, w);
	}
	dfs(1, 0);
	printf("%lld\n", ans);
}