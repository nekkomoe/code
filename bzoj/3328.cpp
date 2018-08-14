#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, p;
struct Mat {
	ll a[2][2];
	ll *operator [] (int x) { return a[x]; }
	Mat() { memset(a, 0, sizeof a); }
	Mat operator * (Mat b) {
		Mat c;
		for(int i = 0 ; i < 2 ; ++ i)
			for(int j = 0 ; j < 2 ; ++ j)
				for(int k = 0 ; k < 2 ; ++ k)
					c[i][j] = (c[i][j] + a[i][k] * b[k][j] % p) % p;
		return c;
	}
};

Mat pw(Mat a, ll n) {
	Mat c; c[0][0] = c[1][1] = 1;
	for( ; n ; n >>= 1, a = a * a) if(n & 1) c = c * a;
	return c;
}

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
	return r;
}
ll calc(ll x) {
	Mat m;
	m[0][0] = x + 1, m[0][1] = x;
	m[1][0] = x, m[1][1] = 1;	
	m = pw(m, n);
	return m[0][0];
}
namespace getg {
	int sig[int(1e7)];
	int get(int p) {
		int x = p - 1, tot = 0;
		for(int i = 2 ; 1ll * i * i <= x ; ++ i) {
			if(x % i) continue;
			sig[++ tot] = i;
			if(x / i > i) sig[++ tot] = x / i;
		}
		for(int g = 2 ; ; ++ g) {
			bool flag = 1;
			for(int i = 1 ; i <= tot ; ++ i) {
				if(pw(g, sig[i]) == 1) {
					flag = 0;
					break;
				}
			}
			if(flag) return g;
		}
		assert(0);
		return -1;
	}
}

void sol() {
	scanf("%lld%lld%lld", &n, &k, &p);
	ll g = getg :: get(p);
	ll wn = pw(g, (p - 1) / k);
	ll w = 1, ans = calc(w);
	for(int i = 1 ; i < k ; ++ i) {
		w = w * wn % p;
		ans = (ans + calc(w)) % p;
	}
	ans = (ans % p + p) % p;
	printf("%lld\n", ans * pw(k, p - 2) % p);
}
int main() {
	int T; scanf("%d", &T);
	while(T --) sol();
}
