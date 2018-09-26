#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, T = 50;
ll fac[100], invfac[100];
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

int main() {
	int n, m; cin >> n >> m;
	fac[0] = 1; for(int i = 1 ; i <= T ; ++ i) fac[i] = fac[i - 1] * i % mod;
	invfac[0] = 1, invfac[T] = pw(fac[T], mod - 2);
	for(int i = T - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
	ll ans = 1;
	for(int i = 2 ; i * i <= m ; ++ i) {
		if(m % i) continue;
		int tot = 0;
		while(m % i == 0) ++ tot, m /= i;
		ll r = invfac[tot];
		for(int j = n ; j <= tot + n - 1 ; ++ j) r = r * j % mod;
		ans = ans * r % mod;
	}
	if(m > 1) {
		int tot = 1;
		ll r = invfac[tot];
		for(int j = n ; j <= tot + n - 1 ; ++ j) r = r * j % mod;
		ans = ans * r % mod;
	}
	cout << ans << endl;
}
