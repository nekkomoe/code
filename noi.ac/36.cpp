#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1010; struct T { int i, j; } a[N * N];
int n, m, q, ans[N][N], x[N], y[N];

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1, x ; j <= m ; ++ j)
			scanf("%d", &x), a[x] = (T) { i, j };
	for(int i = n * m ; i ; -- i)
		++ ans[++ x[a[i].i]][++ y[a[i].j]];
	for(int i = 1, x, y ; i <= q ; ++ i)
		scanf("%d%d", &x, &y),
		printf("%d\n", ans[x][y]);
}
