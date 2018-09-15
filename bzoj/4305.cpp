#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

const int N = 3e5 + 10, mod = 1e9 + 7;

int n, m, k, a[N], fac[N], invfac[N], vis[N];

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
} 

ll f[N];

ll C(ll n, ll m) {
	if(n < m) return 0;
	return 1ll * fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
	read(n), read(m), read(k);
	for(int i = 1 ; i <= n ; ++ i) read(a[i]);
	fac[0] = 1, invfac[0] = 1;
	for(int i = 1 ; i <= n ; ++ i) fac[i] = 1ll * fac[i - 1] * i % mod, invfac[i] = pw(fac[i], mod - 2);
	for(int i = 1 ; i <= n ; ++ i)
		vis[a[i]] ++;
	for(int i = 1 ; i <= m ; ++ i) {
		int x = 0;
		for(int j = i ; j <= m ; j += i) {
			x += vis[j];
		}
		int y = n - x;
		if(y > k) continue;
		int z = k - y;
		f[i] = pw(m / i, y) * C(x, z) % mod * pw(m / i - 1, z) % mod;
	}
	for(int i = m ; i ; -- i) {
		for(int j = i + i ; j <= m ; j += i) {
			f[i] = (1ll * f[i] - f[j]) % mod;
		}
	}
	for(int i = 1 ; i <= m ; ++ i) {
		ll ans = (1ll * f[i] + mod) % mod;
		if(i > 1) putchar(' ');
		printf("%lld", ans);
		if(i == m) puts("");
	}
}
