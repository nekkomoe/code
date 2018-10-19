#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e7 + 10, mod = 1e9 + 7, T = 1e7;
int fac[N], invfac[N];

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

bool vis[N]; int tot, f[N];

int C(int n, int m) {
	return n >= m ? (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod : 0;
}

int main() {
	int l, r; scanf("%d%d", &l, &r);
	fac[0] = invfac[0] = 1;
	for(int i = 1 ; i <= T ; ++ i) fac[i] = (ll) fac[i - 1] * i % mod;
	invfac[T] = pw(fac[T], mod - 2);
	for(int i = T - 1 ; i ; -- i) invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
	
	for(int i = l ; i <= r ; ++ i) {
		if(!vis[i]) {
			++ tot;
			for(int j = i ; j <= r ; j += i) {
				vis[j] = 1;
			}
		}
	}
	
	int n = r - l + 1, ans = 0;
	for(int i = tot ; i <= n ; ++ i) ans = (ans + (ll) fac[i] % mod * invfac[i - tot] % mod) % mod;
	ans = (ll) ans * tot % mod * fac[n - tot] % mod;
	if(ans < 0) ans += mod;
	printf("%d\n", ans);
}
