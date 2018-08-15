#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
int f[N][N], n, k;
int main() {
	scanf("%d%d", &n, &k);
	f[0][0] = 1;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= min(i, k) ; ++ j)
			f[i][j] = (1ll * f[i - 1][j - 1] + f[i - j][j]) % 998244353;
	printf("%d\n", f[n][k]);
}
