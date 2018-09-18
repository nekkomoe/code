#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20000 + 10;
int n, a[N], mn[N], mx[N];
bool check(ll x) {
	mn[1] = mx[1] = a[1];
	for(int i = 2 ; i <= n ; ++ i)
		mx[i] = min(a[1] - mn[i - 1], a[i]),
		mn[i] = max(a[1] + a[i] + a[i - 1] - mx[i - 1] - x, 0ll);
	return mn[n] == 0;
}
int main() {
	scanf("%d", &n);
	ll l = 0, r, ans;
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &a[i]);
		l = max(l, 1ll * a[i] + a[i - 1]);
	}
	r = 2 * l + 10;
	while(l <= r) {
		ll mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
}
