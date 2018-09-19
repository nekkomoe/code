#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
int f[N][N], n, ans[N][N];
int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &f[i][i]), ans[i][i] = f[i][i];
	for(int len = 2 ; len <= n ; ++ len)
		for(int i = 1 ; i + len - 1 <= n ; ++ i) {
			int j = i + len - 1;
			f[i][j] = f[i][j - 1] ^ f[i + 1][j];
			ans[i][j] = max(f[i][j], max(ans[i + 1][j], ans[i][j - 1]));
		}
	scanf("%d", &n);
	for(int i = 1, l, r ; i <= n ; ++ i) scanf("%d%d", &l, &r), printf("%d\n", ans[l][r]);
}
