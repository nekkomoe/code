#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e7 + 10, mod = 1e9 + 7;
int n, pri[N], tot, c[N]; bool vis[N];

int main() {
	scanf("%d", &n);
	for(int i = 2 ; i <= n ; ++ i) {
		if(!vis[i]) {
			pri[++ tot] = i;
		}
		for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
			vis[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
		}
	}
	for(int i = 1 ; i <= tot ; ++ i) {
		int p = pri[i];
		for(ll j = p ; j <= n ; j *= p) c[i] += n / j;
	}
	ll ans = 1;
	for(int i = 1 ; i <= tot ; ++ i) ans = (2ll * c[i] % mod + 1) % mod * ans % mod;
	printf("%lld\n", ans);
}
