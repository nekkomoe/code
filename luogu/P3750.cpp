#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10, mod = 100003;
int n, k;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

ll f[N]; int a[N];

vector<int> g[N];

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &a[i]);
		for(int j = i ; j <= n ; j += i) {
			g[j].push_back(i);
		}
	}
	int tot = 0;
	for(int i = n ; i ; -- i) {
		if(a[i]) {
			for(int j = 0 ; j < g[i].size() ; ++ j) {
				a[g[i][j]] ^= 1;
			}
			++ tot;
		}
	}
	f[n] = 1;
	for(int i = n - 1 ; i > k ; -- i)
		f[i] = (n + (n - i) * f[i + 1] % mod) * pw(i, mod - 2) % mod;
	for(int i = 1 ; i <= k ; ++ i) f[i] = 1;
	ll ans = 0;
	for(int i = tot ; i >= 1 ; -- i)
		ans = (ans + f[i]) % mod;
	for(int i = 1 ; i <= n ; ++ i) ans = ans * i % mod;
	if(ans < 0) ans += mod;
	printf("%lld\n", ans);
}
