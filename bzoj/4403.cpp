#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10, ttt = 1e6 + 2, mod = 1e6 + 3;
int n, T, l, r, fac[N], invfac[N];

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

ll C(int n, int m) {
	if(n < m) return 0;
	if(m == 0) return 1;
	if(n < mod) return (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod;
	return C(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}

int main() {
	fac[0] = 1;
	for(int i = 1 ; i <= ttt ; ++ i) fac[i] = (ll) fac[i - 1] * i % mod;
	invfac[0] = 1, invfac[ttt] = pw(fac[ttt], mod - 2);
	for(int i = ttt - 1 ; i ; -- i) invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
	
//	cout << C(3, 2) << endl;
	
	scanf("%d", &T);
	while(T --)
		scanf("%d%d%d", &n, &l, &r),
		printf("%lld\n", ((C(n + r - l + 1, n) - 1) % mod + mod) % mod);
}
