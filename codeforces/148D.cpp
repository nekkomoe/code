#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;
int w, b;
double f[N][N];
double c(int i, int j) { return 1.0 * i / j; }

int main() {
	scanf("%d%d", &w, &b);
	for(int i = 1 ; i <= w ; ++ i) f[i][0] = 1;
	for(int j = 0 ; j <= b ; ++ j) f[0][j] = 0;
	for(int i = 1 ; i <= w ; ++ i)
		for(int j = 1 ; j <= b ; ++ j) {
			f[i][j] = c(i, i + j);
			if(j - 3 >= 0)
				f[i][j] += f[i][j - 3] * c(j, i + j) * c(j - 1, i + j - 1) * c(j - 2, i + j - 2);
			if(j - 2 >= 0)
				f[i][j] += f[i - 1][j - 2] * c(j, i + j) * c(j - 1, i + j - 1) * c(i, i + j - 2);
		}
	printf("%.12lf\n", f[w][b]);
}
