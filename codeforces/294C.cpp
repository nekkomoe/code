#include <bits/stdc++.h>
using namespace std;
const int N = 1010, mod = 1e9 + 7;
int n, m, fac[N], invfac[N];
typedef long long ll;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}
int pos[N];
int main() {
	cin >> n >> m;
	fac[0] = invfac[1] = 1;
	for(int i = 1 ; i <= n ; ++ i) fac[i] = (ll) fac[i - 1] * i % mod;
	invfac[n] = pw(fac[n], mod - 2);
	for(int i = n - 1 ; i ; -- i) invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
	for(int i = 1 ; i <= m ; ++ i) cin >> pos[i];
	sort(pos + 1, pos + 1 + m);
	ll ans = fac[n - m];
	pos[++ m] = n + 1;
	for(int i = 1 ; i <= m ; ++ i) {
		int len = pos[i] - pos[i - 1] - 1;
		if(len >= 1) {
			if(1 < i && i < m) ans = ans * pw(2, len - 1) % mod;
			ans = ans * invfac[len] % mod;
		}
	}
	cout << ans << endl;
}