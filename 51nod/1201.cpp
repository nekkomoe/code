#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10, mod = 1e9 + 7, m = 350;
int f[N][m + 10], n;

int main() {
	scanf("%d", &n);
	f[0][0] = 1;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= min(i, m) ; ++ j)
			f[i][j] = ((long long) f[i - j][j - 1] + f[i - j][j]) % mod;
	
	for(int i = n ; i <= n ; ++ i) {
		int ans = 0;
		for(int j = 1 ; j <= m ; ++ j) {
			ans = ((long long) ans + f[i][j]) % mod;
		}
		printf("%d\n", ans);
	}
}
