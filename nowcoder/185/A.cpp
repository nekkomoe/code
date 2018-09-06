#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100000 + 10;
ll x[N];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

void sol() {
	int a, b;
	scanf("%d%d", &a, &b);
	ll cd = x[gcd(a, b)];
	ll t = cd * (cd - 1) / 2;
	printf("%lld\n", x[a] * x[b] - t);
}

int main() {
	for(int i = 1 ; i <= 100000 ; ++ i) {
		for(int j = i ; j <= 100000 ; j += i) {
			++ x[j];
		}
	}
	int T; scanf("%d", &T);
	while(T --) sol();
}
