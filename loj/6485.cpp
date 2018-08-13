// type 1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p = 998244353, g = 3;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
	return r;
}
ll n, s, a[4], w[4], c[4];
int main() {
	int T; scanf("%d", &T);
	ll wn = pw(g, (p - 1) / 4), inv4 = pw(4, p - 2);
	w[0] = 1; for(int i = 1 ; i < 4 ; ++ i) w[i] = w[i - 1] * wn % p;
	while(T --) {
		scanf("%lld%lld", &n, &s);
		for(int i = 0 ; i < 4 ; ++ i) scanf("%lld", &a[i]), c[i] = 0;
		for(int i = 0 ; i < 4 ; ++ i) {
			for(int j = 0 ; j < 4 ; ++ j)
				c[i] = (c[i] + pw((1 + w[j] * s % p) % p, n) * pw(w[i * j % 4], p - 2) % p) % p;
			c[i] = c[i] * inv4 % p;
		}
		ll sum = 0;
		for(int i = 0 ; i < 4 ; ++ i) sum = (sum + a[i] * c[i] % p) % p;
		printf("%lld\n", sum);
	}
}

// type 2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p = 998244353, g = 3;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
	return r;
}
ll n, s, a[4], w[4], c[4];
int main() {
	int T; scanf("%d", &T);
	ll wn = pw(g, (p - 1) / 4), inv4 = pw(4, p - 2);
	w[0] = 1; for(int i = 1 ; i < 4 ; ++ i) w[i] = w[i - 1] * wn % p;
	while(T --) {
		scanf("%lld%lld", &n, &s);
		for(int i = 0 ; i < 4 ; ++ i) scanf("%lld", &a[i]), c[i] = 0;
		for(int i = 0 ; i < 4 ; ++ i) {
			for(int j = 0 ; j < 4 ; ++ j)
				c[i] = (c[i] + pw((w[j] + s) % p, n) * pw(w[j], i) % p) % p;
			c[i] = c[i] * inv4 % p;
		}
		ll sum = 0;
		for(int i = 0 ; i < 4 ; ++ i) sum = (sum + a[(n + i) % 4] * c[i] % p) % p;
		printf("%lld\n", sum);
	}
}
