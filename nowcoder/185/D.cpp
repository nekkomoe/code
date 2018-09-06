#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;

ll calc(ll n) {
	if(n <= 0) return 0;
	ll l = 1, r = 1e9, ans = 0;
	while(l <= r) {
		ll mid = (l + r) >> 1;
		if(mid * mid <= n) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return ans;
}

int main() {
	ll n; scanf("%lld", &n);
	printf("%lld\n", calc(n));
}
