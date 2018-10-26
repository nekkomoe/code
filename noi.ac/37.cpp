#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 5010;
int n, m, p;
ll f[N][N], g[N][N];

int main() {
	scanf("%d%d%d", &n, &m, &p);
	f[0][0] = g[0][0] = 1; 
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= min(i, m - 1) ; ++ j) {
			g[i][j] = f[i][j] = (f[i - 1][j - 1] * (m - j + 1) % p + g[i - 1][j]) % p;
		}
		for(int j = i ; j ; -- j) (g[i][j] += g[i][j + 1]) %= p;
	}
	printf("%lld\n", g[n][1]);
}
