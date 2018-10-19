#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 2e3 + 10;
int n, m, f[N], c[N][N], w[N];

int main() {
	scanf("%d%d", &n, &m);
	f[0] = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &w[i]);
		for(int j = m ; j >= w[i] ; -- j)
			f[j] = (f[j] + f[j - w[i]]) % 10;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		c[i][0] = 1;
		for(int j = 1 ; j <= m ; ++ j) {
			if(j >= w[i]) c[i][j] = (f[j] - c[i][j - w[i]]) % 10;
			else c[i][j] = f[j];
		}
	}
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= m ; ++ j) {
			printf("%d", (c[i][j] % 10 + 10) % 10);
		}
		puts("");
	}
}
