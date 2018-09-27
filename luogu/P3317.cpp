#include <bits/stdc++.h>
using namespace std;
const int N = 60; const double eps = 1e-8;

double a[N][N];

int n;

int main() {
	scanf("%d", &n);
	double prod = 1;
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			scanf("%lf", &a[i][j]);
			if(fabs(a[i][j]) < eps) a[i][j] = eps;
			if(fabs(1 - a[i][j]) < eps) a[i][j] = 1 - eps;
			if(i < j) prod *= 1 - a[i][j];
			a[i][j] /= 1 - a[i][j];
		}
		
	for(int i = 1 ; i <= n ; ++ i) {
		a[i][i] = 0;
		for(int j = 1 ; j <= n ; ++ j)
			if(i != j)
				a[i][i] -= a[i][j];
	}
	
	-- n;
	
	for(int i = 1 ; i <= n ; ++ i) {
		int t = i;
		for(int j = i ; j <= n ; ++ j) if(fabs(a[j][i]) > fabs(a[t][i])) t = j;
		for(int j = i ; j <= n ; ++ j) swap(a[i][j], a[t][j]);
		for(int j = i + 1 ; j <= n ; ++ j) {
			double p = a[j][i] / a[i][i];
			for(int k = i ; k <= n ; ++ k) {
				a[j][k] -= a[i][k] * p;
			}
		}
		if(fabs(a[i][i]) < eps) { prod = 0; break; }
		prod *= a[i][i];
	}
	
	printf("%.20lf\n", fabs(prod));
}
