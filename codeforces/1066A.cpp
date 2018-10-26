#include <bits/stdc++.h>
using namespace std; typedef long long ll;

void sol() {
	ll L, v, l, r;
	cin >> L >> v >> l >> r;
	ll ans = L / v - r / v + (l - 1) / v;
	cout << ans << endl;
}

int main() {
	ios :: sync_with_stdio(0);
	ll T; cin >> T;
	while(T --) sol();
}
