#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll m, a, c, x, n, g, ans;

ll mul(ll a, ll b) {
	// return a * b % m;
	a = (a % m + m) % m;
	b = (b % m + m) % m;
	ll r = 0;
	for( ; b ; b >>= 1, a = (a + a) % m)
		if(b & 1)
			r = (r + a) % m;
	return r;
}

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = mul(a, a))
		if(b & 1)
			r = mul(r, a);
	return r;
}

ll get(ll n) {

	// ll r = 0;
	// for(ll i = 0 ; i <= n ; ++ i) {
	// 	r = (r + pw(a, i)) % m;
	// 	printf("calc %lld^%lld\n", a, i);
	// }
	// return r;

	if(n == 0) return 1;
	else if(n & 1)
		return (get(n - 1) + pw(a, n)) % m;
	else
		return (mul(get(n / 2), pw(a, n / 2) + 1) - pw(a, n / 2)) % m;
}

int main() {
	cin >> m >> a >> c >> x >> n >> g;
	ans = mul(pw(a, n), x);
	// cout << "n - 1 = " << n - 1 << ": " << get(n - 1) << endl;
	ans = (ans + mul(c, get(n - 1))) % m;
	ans = (ans % g + g) % g;
	cout << ans << endl;
}
