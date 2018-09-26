#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, m, k, a[1ll << 22]; ll ans;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

int main() {
	freopen("loneliness.in", "r", stdin);
	freopen("loneliness.out", "w", stdout); 
	scanf("%*d%d%d%d", &n, &m, &k);
	for(int i = 1, x ; i <= m ; ++ i) scanf("%d", &x), ++ a[x];
	for(int i = 0 ; i < n ; ++ i)
		for(int s = 1 ; s < (1 << (n + 1)) ; ++ s)
			if((s >> i) & 1)
				a[s - (1 << i)] += a[s];
	for(int s = 1 ; s < (1 << n) ; ++ s) {
		int cnt = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			if((s >> (i - 1)) & 1) {
				++ cnt;
			}
		}
		ans = (ans + (cnt & 1 ? 1 : -1) * pw(a[s], k) % mod) % mod;
	}
	ans = (ans + mod) % mod;
	printf("%lld\n", ans);
}
