#include <bits/stdc++.h>
using namespace std;
const int N = 1010, M = 210, mod = 1000000007;
int f[2][M][M][2], n, m, k;
char A[N], B[M];

int getsum(int a, int b, int c = 0) {
	return ((1ll * a + b) % mod + c) % mod;
}

int main() {
	int p = 0;
	scanf("%d%d%d%s%s", &n, &m, &k, A + 1, B + 1);
	f[p][0][0][0] = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		p ^= 1;
		memset(f[p], 0, sizeof f[p]);
		f[p][0][0][0] = 1;
		for(int j = 1 ; j <= m ; ++ j) {
			for(int k = 1 ; k <= :: k ; ++ k) {
				f[p][j][k][0] = getsum(f[p ^ 1][j][k][0], f[p ^ 1][j][k][1]);
				if(A[i] == B[j]) {
					f[p][j][k][1] = getsum(f[p ^ 1][j - 1][k - 1][0], f[p ^ 1][j - 1][k][1], f[p ^ 1][j - 1][k - 1][1]);
				}
			}
		}
	}
	
	printf("%d\n", getsum(f[p][m][k][0], f[p][m][k][1]));
}
