#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x, y;

void exgcd(ll &x, ll &y, ll a, ll b) {
	if(!b) x = 1, y = 0;
	else exgcd(y, x, b, a % b), y -= a / b * x;
}

void sol() {
	ll a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
	if(a < b) swap(a, b);
	ll d = __gcd(a, b);
	if(c % d) return puts("0"), void();
	
	a /= d, b /= d, c /= d;
	exgcd(x, y, a, b);
	
	x = (x % b + b) % b;
	x = c % b * x % b;
	y = (c - a * x) / b;
	if(y < 0) return puts("0"), void();
	printf("%lld\n", y / a + 1);
}

int main() {
	freopen("cake.in", "r", stdin);
	freopen("cake.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T --) sol(); 
}
