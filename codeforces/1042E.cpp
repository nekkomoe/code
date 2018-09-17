#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010, mod = 998244353;
int n, m, r, c; struct P {int val, x, y; } p[N * N];
bool operator < (P a, P b) { return a.val < b.val; }
ll f[N * N], Ti, Tj, Tii, Tjj, sum, cnt;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

ll pls(ll a = 0, ll b = 0, ll c = 0) {
	return ((a + b) % mod + c) % mod; 
}

int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> m; int tot = 0;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			cin >> p[++ tot].val, p[tot].x = i, p[tot].y = j;
	cin >> r >> c;
	sort(p + 1, p + 1 + tot);
	for(int i = 1 ; i <= tot ; ++ i) {
		ll p1 = sum;
		ll p2 = Tii;
		ll p3 = Tjj;
		ll p4 = 1ll * cnt * p[i].x % mod * p[i].x % mod;
		ll p5 = 1ll * cnt * p[i].y % mod * p[i].y % mod;
		ll p6 = -2ll * p[i].x % mod * Ti % mod;
		ll p7 = -2ll * p[i].y % mod * Tj % mod;
		f[i] = pls(pls(p1, p2, p3), pls(p4, p5), pls(p6, p7)) * pw(cnt, mod - 2) % mod;
		if(p[i].x == r && p[i].y == c) {
			f[i] = (f[i] % mod + mod) % mod;
			cout << f[i] << endl;
			exit(0);
		}
		if(p[i].val != p[i + 1].val) {
			for(int j = i ; j >= 1 ; -- j) {
				if(p[j].val != p[i].val) break;
				Ti += p[j].x, Tj += p[j].y;
				Tii += 1ll * p[j].x * p[j].x % mod, Tjj += 1ll * p[j].y * p[j].y % mod;
				Ti %= mod, Tj %= mod, Tii %= mod, Tjj %= mod;
				sum += f[j], sum %= mod;
				++ cnt;
			}
		}
	}
}
