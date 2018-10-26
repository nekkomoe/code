#include <bits/stdc++.h>
using namespace std; typedef long long ll;

ll f[110]; const int T = 100;

void init() {
	f[1] = f[2] = 1;
	for(int i = 3 ; i <= 100 ; ++ i) f[i] = f[i - 1] + f[i - 2];
}

void sol() {
	ll x; scanf("%lld", &x);
	ll ans = 0;
	while(x) {
		++ ans;
		if(x == 1) break;
		int i = lower_bound(f + 1, f + 1 + T, x) - f;
		x = min(f[i] - x, x - f[i - 1]);
	}
	printf("%lld\n", ans);
}

int main() {
	init();
	int T; scanf("%d", &T);
	while(T --) sol();
}
