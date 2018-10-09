#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
// typedef long long ll;
const int N = 2e5 + 10;

ll n, s, l, h[N], a[N];

bool check(ll mid) {
	ll sum = s;
	for(int i = 1 ; i <= n ; ++ i) {
		ll h = :: h[i] + a[i] * mid;
		if(h >= l) {
			sum -= h;
			if(sum <= 0) return 1;
		}
	}
	return 0;
}

int main() {
	long long _n, _s, _l;
	cin >> _n >> _s >> _l;
	n = _n, s = _s, l = _l;
	for(int i = 1, _h ; i <= n ; ++ i) cin >> _h, h[i] = _h;
	for(int i = 1, _a ; i <= n ; ++ i) cin >> _a, a[i] = _a;
	ll l = 0, r = 1e18, ans = 0;
	while(l <= r) {
		ll mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << (long long) ans << endl;
}