#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10; int n, m;
struct E { int v, w; }; vector<E> G[N], g[N]; int cnt, bel[N];
int sta[N], top, ins[N], dfn[N], low[N], clk; ll val[N], f[N];
void dfs(int u) {
	sta[++ top] = u, ins[u] = 1;
	dfn[u] = low[u] = ++ clk;
	for(E e: G[u]) {
		int v = e.v;
		if(!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(dfn[u] == low[u]) {
		int v; ++ cnt;
		do {
			v = sta[top]; -- top; ins[v] = 0;
			bel[v] = cnt;
		} while(v != u);
	}
}

ll go(int u) {
	if(f[u] != -1) return f[u];
	ll res = 0;
	for(E e: g[u]) {
		int v = e.v, w = e.w;
		res = max(res, go(v) + w);
	}
	return f[u] = res + val[u];
}

int main() {
	int n, m, S; scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w ; i <= m ; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back((E) { v , w });
	}
	memset(f, -1, sizeof f);
	for(int i = 1 ; i <= n ; ++ i)
		if(!dfn[i])
			dfs(i);
	for(int u = 1 ; u <= n ; ++ u) {
		for(E e: G[u]) {
			int v = e.v, w = e.w;
			if(bel[u] == bel[v]) {
				ll t = (ll) (1 + sqrt(1 + 8 * w)) / 2;
				val[bel[u]] += t * w - t * (t - 1) * (t + 1) / 6;
			} else {
				g[bel[u]].push_back({ bel[v], w });
			}
		}
	}
	scanf("%d", &S);
	printf("%lld\n", go(bel[S]));
}
