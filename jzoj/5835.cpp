#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e7 + 10;
ll L, R, k;

bool vis[N];

#define v(x) vis[x - L]

int pri[N], tot; bool privis[N];

int main() {
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	scanf("%lld%lld%lld", &L, &R, &k);
	ll n = min((ll) 1e7, k);
	for(int i = 2 ; i <= n ; ++ i) {
		if(!privis[i]) pri[++ tot] = i;
		for(int j = 1 ; j <= tot && pri[j] * i <= n ; ++ j) {
			privis[pri[j] * i] = 1;
			if(i % pri[j] == 0) break;
		}
	}
	for(int i = 1 ; i <= tot ; ++ i) {
		ll x = pri[i];
		for(ll j = L / x + (L % x != 0) ; j * x <= R ; ++ j) {
//			assert(j * x >= L);
			if(j == 1) continue;
			v(j * x) = 1;
		}
	}
	ll ans = 0;
	for(ll i = L ; i <= R ; ++ i)
		if(!v(i))
			ans ^= i;
	printf("%lld\n", ans);
}
