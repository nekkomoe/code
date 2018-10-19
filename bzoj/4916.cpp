#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10, mod = 1e9 + 7, T = 1e6;
int n, pri[N], tot, phi[N], vis[N], inv6, inv2; ll cnt[N];

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

ll f(int n) {
	if(n <= T) return phi[n];
	if(cnt[:: n / n] != -1) return cnt[:: n / n];
	ll res = (ll) n * ((ll) n + 1) % mod * (2ll * n % mod + 1) % mod * inv6 % mod;
	for(int i = 2, j ; i <= n ; i = j + 1) {
		j = n / (n / i);
		res = (res - ((ll) i + j) * (j - i + 1) % mod * inv2 % mod * f(n / i) % mod) % mod;
	}
	if(res < 0) res += mod;
	cnt[:: n / n] = res;
	return res;
}

int main() {
	memset(cnt, -1, sizeof cnt);
	scanf("%d", &n);
	puts("1");
	inv2 = pw(2, mod - 2);
	inv6 = pw(6, mod - 2);
	phi[1] = 1;
	for(int i = 2 ; i <= T ; ++ i) {
		if(!vis[i]) {
			pri[++ tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
			vis[i * pri[j]] = 1;
			if(i % pri[j] == 0) {
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			} else {
				phi[i * pri[j]] = phi[i] * (pri[j] - 1);
			}
		}
	}
	for(int i = 1 ; i <= T ; ++ i) phi[i] = ((ll) phi[i - 1] + (ll) i * phi[i] % mod) % mod;
	printf("%lld\n", (f(n) % mod + mod) % mod);
}
