#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
typedef long long ll;
//#define ll __int128
int n, m, k[20], vis[N];

ll x, y, ans;

void exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= x * (a / b);
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll getlcm(ll a, ll b) {
	if(!a || !b) return a | b;
	return a / gcd(a, b) * b;
}

int main() {
	freopen("sazetak.in", "r", stdin);
	freopen("sazetak.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= m ; ++ i) scanf("%d", &k[i]);
	int lim = pow(3, m);
	for(int s = 0 ; s < lim ; ++ s) {
		ll lcm1 = 0, lcm2 = 0, c1 = 0, c2 = 0, flag = 0;
		for(int i = 1, ss = s ; i <= m ; ++ i, ss /= 3) {
			if(ss % 3 == 1) lcm1 = getlcm(lcm1, k[i]), ++ c1;
			else if(ss % 3 == 2) lcm2 = getlcm(lcm2, k[i]), ++ c2;
			if(lcm1 > n || lcm2 > n) { flag = 1; break; }
		}
		if(gcd(lcm1, lcm2) != 1 || !c1 || !c2 || flag) continue;
		exgcd(lcm1, lcm2, x, y);
		ll lcm = lcm1 * lcm2;
		x = (x % lcm2 + lcm2) % lcm2;
		x = (x * lcm1 % lcm + lcm) % lcm;
		if(x + 1 >= n) continue;
		if((c1 + c2) & 1) ans -= (n - x - 1) / lcm + 1;
		else ans += (n - x - 1) / lcm + 1;
	}
	for(int i = 1 ; i <= m ; ++ i) {
		if(n % k[i] == 1) {
			++ ans;
			break;
		}
	}
	printf("%lld\n", (long long) ans);
}
