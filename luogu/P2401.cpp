#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1010, mod = 2015;
int n, k;
ll f[N][N];

int main() {
	scanf("%d%d", &n, &k);
	f[0][0] = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		f[i][0] = f[i - 1][0];
		for(int j = 1 ; j <= k ; ++ j)
			f[i][j] = (f[i - 1][j] * (j + 1) % mod + (i - j) * f[i - 1][j - 1] % mod) % mod;
	}
	printf("%lld\n", f[n][k]);
} 
