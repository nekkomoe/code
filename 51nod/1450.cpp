#include <bits/stdc++.h>
using namespace std;
const int N = 4010;
double f[N][N];
struct P { int x, y; } p[N];
bool operator < (P a, P b) { return a.y < b.y; }
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0 ; i < n ; ++ i) scanf("%d%d", &p[i].x, &p[i].y);
	sort(p, p + n);
	for(int i = 0 ; i < N ; ++ i) for(int j = 0 ; j < N ; ++ j) f[i][j] = 1e20;
	m -= n;
	f[n][m] = 0;
	for(int i = n - 1 ; i >= 0 ; -- i) {
		int x = p[i].x, y = p[i].y;
		for(int j = 0 ; j < m ; ++ j) {
			f[i][j] = min(
				  1000.0 / (x + y)
				+ f[i + 1][j] * x / (x + y)
				+ f[i + 1][j + 1] * y / (x + y),

				f[i + 1][j + 1] + 1000.0 / y
			);
		}
		f[i][m] = 1000.0 / (x + y) + f[i + 1][m];
	}
	printf("%lf\n", f[0][0]);
}
