#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, p[3] = { 998244353, 23333, 2333 };
char s[N];
int a[N], b[N], c[N], vis[N], ans[N], tot, n, m;
int calc(int v) {
	int x = 0, y = 0, z = 0;
	for(int i = n ; ~ i ; -- i) {
		x = ((ll) v * (a[i] + x)) % p[0];
		y = ((ll) v * (b[i] + y)) % p[1];
		z = ((ll) v * (c[i] + z)) % p[2];
	}
	if(x) for(int j = v ; j <= m ; j += p[0]) vis[j] = 1;
	if(y) for(int j = v ; j <= m ; j += p[1]) vis[j] = 1;
	if(z) for(int j = v ; j <= m ; j += p[2]) vis[j] = 1;
	return x || y || z;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0 ; i <= n ; ++ i) {
		scanf("%s", s + 1);
		int sig = s[1] == '-';
		for(int j = sig + 1 ; s[j] ; ++ j) {
			a[i] = ((ll) a[i] * 10 + s[j] - '0') % p[0];
			b[i] = ((ll) b[i] * 10 + s[j] - '0') % p[1];
			c[i] = ((ll) c[i] * 10 + s[j] - '0') % p[2];
		}
		if(sig) {
			a[i] = (p[0] - a[i]) % p[0];
			b[i] = (p[1] - b[i]) % p[1];
			c[i] = (p[2] - c[i]) % p[2];
		}
	}
	for(int i = 1 ; i <= m ; ++ i) {
		if(!vis[i] && !calc(i))
			ans[++ tot] = i;
	}
	printf("%d\n", tot);
	for(int i = 1 ; i <= tot ; ++ i) {
		printf("%d\n", ans[i]);
	}
}
