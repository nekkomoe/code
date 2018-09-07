#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	int n; cin >> n;
	ll ans = 0, x, f = 0, g = 0, mn = 1e9 + 10;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> x;
		if(n == 1) return (cout << x), 0;
		mn = min(abs(x), mn), f |= x >= 0, g |= x <= 0;
		ans += abs(x);
	}
	if(f && g) cout << ans;
	else cout << ans - 2 * mn;
}
