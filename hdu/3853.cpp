#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010; const double eps = 1e-10;
int n, m;
double p[N][N][3], f[N][N];

int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		memset(f, 0, sizeof f);
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= m ; ++ j)
				for(int k = 0 ; k < 3 ; ++ k)
					scanf("%lf", &p[i][j][k]);
		for(int i = n ; i ; -- i)
			for(int j = m ; j ; -- j)
				if(i == n && j == m)
					f[i][j] = 0;
				else 
					f[i][j] = fabs(p[i][j][0] - 1) < eps ? 0 : (p[i][j][1] * f[i][j + 1] + p[i][j][2] * f[i + 1][j] + 2) / (1 - p[i][j][0]);
		printf("%.3lf\n", f[1][1]);
	}
}
