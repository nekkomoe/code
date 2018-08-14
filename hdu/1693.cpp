#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll f[12][12][1 << 12];
int a[15][15], n, m;

ll sol() {
	memset(f, 0, sizeof f);
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			scanf("%d", &a[i][j]);
	int s = 1 << (m + 1);
	f[0][m][0] = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int k = 0 ; k < (1 << m) ; ++ k) {
			f[i][0][k << 1] = f[i - 1][m][k];
		}
		for(int j = 1 ; j <= m ; ++ j) {
			for(int k = 0 ; k < s ; ++ k) {
				int left = (k >> (j - 1)) & 1;
				int up = (k >> j) & 1;
				int x = (1 << (j - 1)) | (1 << j);
				if(!a[i][j]) {
					if(!left && !up) {
						f[i][j][k] += f[i][j - 1][k];
					}
				} else if(left ^ up) {
					f[i][j][k] += f[i][j - 1][k];
					f[i][j][k ^ x] += f[i][j - 1][k];
				} else {
					f[i][j][k ^ x] += f[i][j - 1][k];
				}
			}
		}
	}
	return f[n][m][0];
}

int main() {
	int T; scanf("%d", &T);
	for(int i = 1 ; i <= T ; ++ i) {
		printf("Case %d: There are %lld ways to eat the trees.\n", i, sol());
	}
}
