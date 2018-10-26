#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f, N = 15;
int a[N][N], n, m, f[N][N][1 << N];

int to(int x) { return 1 << (x - 1); }

int dfs(int u, int dep, int S) {
	int &x = f[u][dep][S]; if(~ x) return x; if(!S) return x = 0; x = inf;
	for(int v = 1 ; v <= n ; ++ v)
		if(a[u][v] != inf && (S & to(v)))
			for(int T = S ; T ; T = (T - 1) & S)
				if(!(T & to(u)) && (T & to(v)))
					x = min(x, dfs(v, dep + 1, T - to(v)) + dfs(u, dep, S - T) + dep * a[u][v]);
	return x;
}

int main() {
	memset(f, -1, sizeof f), memset(a, 0x3f, sizeof a);
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w ; i <= m ; ++ i) scanf("%d%d%d", &u, &v, &w), a[u][v] = a[v][u] = min(a[u][v], w);
	int ans = inf;
	int all = to(n + 1) - 1;
	for(int i = 1 ; i <= n ; ++ i) ans = min(ans, dfs(i, 1, all - to(i)));
	printf("%d\n", ans);
}
