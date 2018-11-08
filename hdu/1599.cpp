#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 10, inf = 0x3f3f3f3f;
int n, m, a[N][N], b[N][N];

void sol() {
	memset(a, 0x3f, sizeof a);
	memset(b, 0x3f, sizeof b);
	for(int i = 1, u, v, w ; i <= m ; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		a[v][u] = a[u][v] = min(a[u][v], w);
		b[v][u] = b[u][v] = min(b[u][v], w);
	}
	int ans = inf;
	for(int k = 1 ; k <= n ; ++ k) {
		for(int i = 1 ; i <= k ; ++ i) {
			for(int j = i + 1 ; j <= k ; ++ j) {
				if(b[i][k] != inf && b[k][j] != inf && a[i][j] != inf) {
					ans = min(ans, b[i][k] + b[k][j] + a[i][j]);
				}
			}
		}
		for(int i = 1 ; i <= n ; ++ i) {
			for(int j = 1 ; j <= n ; ++ j) {
				a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
			}
		}
	}
	if(ans == inf) puts("It's impossible.");
	else printf("%d\n", ans);
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) sol();
}
