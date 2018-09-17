#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[60], vis[60][60]; double p, T, k[60][60], b[60][60];

void dfs(int val, int step) {
	if(vis[val][step]) return ;
	vis[val][step] = 1;
	double k = 0, b = 0, t = val ? p : 0;
	for(int i = 1 ; i <= step ; ++ i) {
		if(val + a[i] > T) break;
		dfs(val + a[i], i);
		k += :: k[val + a[i]][i], b += :: b[val + a[i]][i]; 
	}
	k *= (1 - t) / step;
	b *= (1 - t) / step;
	:: k[val][step] = t / (1 - k);
	:: b[val][step] = (1 + b) / (1 - k); 
}

void sol(int n) {
	memset(vis, 0, sizeof vis);
	for(int i = 1 ; i <= n ; ++ i) cin >> a[i];
	sort(a + 1, a + 1 + n);
	dfs(0, n);
	printf("%.3lf\n", b[0][n]);
}

int main() {
	int n; while(cin >> p >> T >> n) sol(n);
}
