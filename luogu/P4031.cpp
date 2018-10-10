#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10;

ll i, l, r, k, p, m;

ll x, y, d;
void exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) x = 1, y = 0, d = a;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}

namespace getfib {
	struct Mat {
		ll a[2][2];
		Mat() { memset(a, 0, sizeof a); }
		ll *operator [] (int x) { return a[x]; }
		Mat operator * (Mat b) {
			Mat c;
			for(int i = 0 ; i < 2 ; ++ i)
				for(int j = 0 ; j < 2 ; ++ j)
					for(int k = 0 ; k < 2 ; ++ k)
						c[i][j] = (c[i][j] + a[i][k] * b[k][j] % p) % p;
			return c;
		}
	} bs, t;
	Mat pw(Mat a, ll b) {
		Mat r; r[0][0] = r[1][1] = 1;
		for( ; b ; b >>= 1, a = a * a)
			if(b & 1)
				r = r * a;
		return r;
	}
	ll f[100];
	ll getfib(ll n) {

		// f[0] = f[1] = 1;
		// for(int i = 2 ; i <= n ; ++ i) f[i] = f[i - 1] + f[i - 2];
		// return f[n];

		// cout << "pow of: " << n << endl;
		bs[0][0] = bs[0][1] = 1;
		t[0][1] = t[1][0] = t[1][1] = 1;
		Mat tmp = bs * pw(t, n);
		return tmp[0][0];
	}
}

ll get(ll x, ll w, ll n) {
	if(n < 0 || x > n) return 0;
	return (n - x) / w + 1;
}

void sol() {
	scanf("%lld%lld%lld%lld%lld%lld", &i, &l, &r, &k, &p, &m);
	// puts("fafa1");
	ll T = (m - i % p * (getfib :: getfib(k - 3) % p) % p) % p; if(T < 0) T += p;
	// cout << "T = " << T << endl;
	ll a = getfib :: getfib(k - 2);
	ll b = p;

	// printf("(%lld, %lld, %lld)\n", a, b, T);

	// puts("fafa2");
	exgcd(a, b, x, y);
	// cout << "T = " << T << " d = " << d << endl;
	if(T % d) return puts("0"), void();
	a /= d, b /= d, T /= d;
	exgcd(a, b, x, y);
	// x = (x % b) * (T % b) % b;
	x *= T;
	// cout << "T / d = " << (T / d) << ' ' << x << ' ' << x % b << ' ' << (x * (T / d) % b) << endl;
	// x = (x % b + b) % b;
	// puts("fafa3");

	// cout << "x = " << x << endl;

	ll ans = get(x, b, r) - get(x, b, l - 1);

	{
		// cout << x << ' ' << a << ' ' << b << ' ' << :: l << ' ' << :: r << endl;
		ll l = (:: l - x) / b; if(:: l - x >= 0 && (:: l - x) % b) ++ l;
		ll r = (:: r - x) / b; if(:: r - x <= 0 && (:: r - x) % b) -- r;
		// cout << l << ' ' << r << endl;
		ans = r - l + 1;
	}

	if(ans < 0) ans = 0;
	printf("%lld\n", ans);
}

int main() {
// 	freopen("data.in", "r", stdin);
	int T; scanf("%d", &T);
	while(T --) sol();
}