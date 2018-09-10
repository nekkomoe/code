#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, m, deg[N];
vector<pair<int, int> > g[N];

double a[N][N];

double sol() {
	for(int i = 1 ; i <= n ; ++ i) {
		if(fabs(a[i][i]) < 1e-8) return 0;
		for(int j = i + 1 ; j <= n ; ++ j) {
			double x = a[j][i] / a[i][i];
			for(int k = i ; k <= n + 1 ; ++ k) {
				a[j][k] -= a[i][k] * x;
			}
		}
	}
	for(int i = n ; i ; -- i) {
		for(int j = i + 1 ; j <= n ; ++ j) {
			a[i][n + 1] -= a[i][j] * a[j][n + 1];
		}
		a[i][n + 1] /= a[i][i];
	}
	return a[1][n + 1];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= m ; ++ i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		g[u].push_back(make_pair(v, w)), ++ deg[u];
		if(u != v) g[v].push_back(make_pair(u, w)), ++ deg[v];
	}
	double ans = 0;
	for(int i = 31 ; ~ i ; -- i) {
		memset(a, 0, sizeof a);
		a[n][n] = 1;
		for(int u = 1 ; u < n ; ++ u) {
			a[u][u] = deg[u];
			for(int j = 0 ; j < g[u].size() ; ++ j) {
				int v = g[u][j].first, w = (g[u][j].second >> i) & 1;
				if(w) ++ a[u][n + 1], ++ a[u][v];
				else -- a[u][v];
			}
		}
		ans += (1 << i) * sol();
	}
	printf("%.3lf\n", ans);
}
