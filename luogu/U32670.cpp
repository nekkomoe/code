#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios :: sync_with_stdio(0);
	int T; cin >> T;
	while(T --) {
		ll l, r; cin >> l >> r;
		ll ans = (l + r) % 9 * (r - l + 1) % 9 * 5 % 9;
		cout << ans << endl;
	}
}
