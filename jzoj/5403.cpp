#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

vector<int> G[N];

int c[N], ans[N], dep[N], fa[N][21], n, from[N];

double calc(int u, int v) { // dep[u] > dep[v]
	return 1.0 * (c[v] - c[u]) / (dep[u] - dep[v]);
}

int main() {
	freopen("lost.in", "r", stdin);
	freopen("lost.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &c[i]);
	for(int i = 2, fa ; i <= n ; ++ i) scanf("%d", &fa), G[fa].push_back(i);
	queue<int> q;
	q.push(1), dep[1] = 1;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int v: G[u]) from[v] = u, dep[v] = dep[u] + 1, q.push(v);
		if(u == 1) continue;
		int x = from[u];
		for(int i = 20 ; ~ i ; -- i) {
			if(fa[x][i] <= 1) continue;
			if(calc(u, fa[x][i]) >= calc(u, fa[fa[x][i]][0])) {
				x = fa[fa[x][i]][0];
			}
		}
		if(x > 1 && calc(u, x) >= calc(u, fa[x][0]))
			x = fa[x][0];
		ans[u] = fa[u][0] = x;
		for(int j = 1 ; j <= 20 ; ++ j) fa[u][j] = fa[fa[u][j - 1]][j - 1];
	}
	for(int i = 2 ; i <= n ; ++ i) printf("%lf\n", calc(i, ans[i]));
}
