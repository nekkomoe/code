#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ll n, k;
	cin >> n >> k;
	ll ans = 0, cnt1 = 0, cnt2 = 0;
	for(ll i = 1 ; i <= n ; ++ i) {
		if(i % k == 0) {
			++ cnt1;
		}
	}
	if(k % 2 == 0) {
		for(ll i = 1 ; i <= n ; ++ i) {
			if(i % k == k / 2) {
				++ cnt2;
			}
		}
	}
	ans = cnt1 * cnt1 * cnt1 + cnt2 * cnt2 * cnt2;
	cout << ans << endl;
}
