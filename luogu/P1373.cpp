#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int f[801][801][17][2], n, m, k, a[801][801];

int sig(int x) {
	return x & 1 ? 1 : -1;
}

int main() {
	scanf("%d%d%d", &n, &m, &k), ++ k; 
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			scanf("%d", &a[i][j]),
			f[i][j][a[i][j] % k][0] = 1;
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			for(int t = 0 ; t < k ; ++ t)
				for(int p = 0 ; p <= 1 ; ++ p)
					f[i][j][t][p] = (1ll * f[i][j][t][p]
						+ f[i - 1][j][((t + sig(p) * a[i][j]) % k + k) % k][p ^ 1]
						+ f[i][j - 1][((t + sig(p) * a[i][j]) % k + k) % k][p ^ 1]) % mod;
	
	ll ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			ans = (1ll * ans + f[i][j][0][1]) % mod;
	printf("%d\n", ans);
}	
