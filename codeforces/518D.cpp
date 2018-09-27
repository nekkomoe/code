#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int n, t;
double p, f[N][N];

int main() {
	cin >> n >> p >> t;
	
	f[0][0] = 1;
	for(int i = 1 ; i <= t ; ++ i)
		for(int j = 0 ; j <= n ; ++ j)
			if(j == n)
				f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j];
			else if(j == 0)
				f[i][j] = f[i - 1][j] * (1 - p);
			else
				f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j] * (1 - p);
	
	double ans = 0;
	for(int i = 0 ; i <= n ; ++ i)
		ans += i * f[t][i];
	printf("%.12lf\n", ans);
}
