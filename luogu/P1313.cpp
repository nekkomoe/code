#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 10007;
ll C[1010][1010];

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

int main() {
	C[0][0] = 1;
	for(int i = 1 ; i <= 1000 ; ++ i) {
		C[i][0] = 1;
		for(int j = 1 ; j <= 1000 ; ++ j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
		}
	}
	ll a, b, k, n, m;
	cin >> a >> b >> k >> n >> m;
	ll ans = pw(b, m) * pw(a, n) % mod * C[k][n] % mod;
	cout << ans << endl;
}
