#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;

int c[N], f[N][N], p, n;

int main() {
	cin >> n >> p;
	f[0][0] = 1;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 0 ; j <= i ; ++ j)
			f[i][j] = (1ll * f[i][j] + f[i - 1][max(j - 1, 0)] + 2 * f[i - 1][j + 1]) % p;
	c[0] = c[1] = 1;
	for(int i = 2 ; i <= n ; ++ i)
		for(int j = 1 ; j <= i ; ++ j)
			c[i] = (c[i] + 1ll * c[j - 1] * c[i - j]) % p;
	int ans = 0;
	for(int i = 0 ; i * 2 <= n ; ++ i)
		ans = (ans + 1ll * c[i] * f[n][i * 2] % p) % p;
	printf("%d\n", ans);
}
