#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m; ll a[N], p[N], atk[N], initatk[N];
multiset<ll> swd; ll cho[N];

ll x, y, d;
void exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) d = a, x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
ll mul(ll a, ll b, ll mod) {
	return (__int128) a * b % mod;
}
ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}

namespace SOL {
	ll c[N], mod[N];
	void sol() {
		ll mx = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			exgcd(cho[i], p[i], x, y);
			mod[i] = p[i] / d;
			if(:: a[i] % d) return puts("-1"), void();
			c[i] = mul(x, :: a[i] / d, mod[i]);
			if(c[i] < 0) c[i] += mod[i];

			mx = max(mx, :: a[i] / cho[i] + (:: a[i] % cho[i] != 0));
		}

		for(int i = 2 ; i <= n ; ++ i) {
			ll T = c[i] - c[i - 1];
			exgcd(mod[i - 1], mod[i], x, y);
			if(T % d) return puts("-1"), void();
			x = mul(x, T / d, mod[i] / d);
			mod[i] = lcm(mod[i - 1], mod[i]);
			c[i] = (c[i - 1] + mul(x, mod[i - 1], mod[i])) % mod[i];
		}

		ll ans = c[n] % mod[n];
		if(ans < 0) ans += mod[n];
		printf("%lld\n", ans);
	}
}

void sol() {
	scanf("%d%d", &n, &m);
	swd.clear();
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &p[i]);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &atk[i]);
	for(int i = 1 ; i <= m ; ++ i) scanf("%lld", &initatk[i]), swd.insert(initatk[i]);
	for(int i = 1 ; i <= n ; ++ i) {
		auto it = *swd.begin() > a[i] ? swd.begin() : -- swd.upper_bound(a[i]);
		cho[i] = *it;
		swd.erase(it);
		swd.insert(atk[i]);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(a[i] > p[i]) {
			ll mx = 0;
			for(int j = 1 ; j <= n ; ++ j) {
				mx = max(mx, a[j] / cho[j] + (a[j] % cho[j] != 0));
			}
			printf("%lld\n", mx);
			return ;
		}
	}
	SOL :: sol();
}

int main() {
	int T; scanf("%d", &T);
	while(T --) sol();
}