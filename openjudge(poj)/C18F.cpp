#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

int n, f[N], vis[N];

ll fac[N], invfac[N];
ll calc(ll n) { return pw(n + 1, n - 1); }
ll C(int n, int m) { if(n < m) return 0; return fac[n] * invfac[m] % mod * invfac[n - m] % mod; }

void sol() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) vis[i] = 0, scanf("%d", &f[i]);
	int sum = n; ll ans = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		if(!vis[i]) {
			int len = 0, j = i;
			while(j <= n) {
				vis[j] = 1;
				++ len;
				j = f[j];
			}
//			printf("C(%d, %d) = %d\n", sum, len, C(sum, len));
			ans = (ans * C(sum, len) % mod * calc(len) % mod) % mod;
			sum -= len;
		}
	}
	ans = (ans % mod + mod) % mod;
	printf("%lld\n", ans);
}

int main() {
	fac[0] = invfac[0] = 1;
	for(int i = 1 ; i < N ; ++ i)
		fac[i] = fac[i - 1] * i % mod,
		invfac[i] = pw(fac[i], mod - 2);
	int T; scanf("%d", &T);
	while(T --) sol();
}
