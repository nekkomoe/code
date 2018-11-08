#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, m, t, x[N], y[N], z[N];
const int T = 5010;
int row[T], col[T], a[T][T];

int main() {
// 	freopen("matrix.in", "r", stdin);
// 	freopen("matrix.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &t);
	for(int i = t ; i ; -- i)
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
	for(int i = 1 ; i <= t ; ++ i) {
		if(x[i] == 1) {
			if(row[y[i]]) continue;
			row[y[i]] = 1;
			for(int j = 1 ; j <= m ; ++ j)
				if(!a[y[i]][j])
					a[y[i]][j] = z[i];
		} else {
			if(col[y[i]]) continue;
			col[y[i]] = 1;
			for(int j = 1 ; j <= n ; ++ j)
				if(!a[j][y[i]])
					a[j][y[i]] = z[i];
		}
	}
	for(int i = 1 ; i <= n ; ++ i, puts(""))
		for(int j = 1 ; j <= m ; ++ j)
			printf("%d ", a[i][j]);
}
