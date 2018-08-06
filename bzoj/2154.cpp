#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e7 + 10, mod = 20101009;

ll f[N], g[N];
int vis[N], p[N], tot, n, m;

int main() {
	scanf("%d%d", &n, &m); if(n > m) swap(n, m);
	f[1] = 1;
	for(int i = 2 ; i <= m ; ++ i) {
		if(!vis[i]) {
			p[++ tot] = i;
			f[i] = (1 - i) % mod;
		}
		for(int j = 1 ; j <= tot && (ll) i * p[j] <= m ; ++ j) {
			vis[i * p[j]] = 1;
			if(i % p[j] == 0) {
				f[i * p[j]] = f[i];
				break;
			} else {
				f[i * p[j]] = (1 - p[j]) * f[i] % mod;
			}
		}
	}
	for(int i = 1 ; i <= m ; ++ i) g[i] = (f[i] * i % mod + g[i - 1]) % mod;
	ll ans = 0;
	for(int i = 1, j ; i <= n ; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		ans += 
			(
			((ll) (1 + n / i) * (n / i) / 2 % mod)
		  * ((ll) (1 + m / i) * (m / i) / 2 % mod) % mod
		  * ((g[j] - g[i - 1]) % mod)
		  ) % mod;
		ans %= mod;
	}
	printf("%lld\n", (ans % mod + mod) % mod);
}
