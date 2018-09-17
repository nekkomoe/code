#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n; ll a[N], s[N], t;
vector<ll> num;
int get(ll n) {
	return lower_bound(num.begin(), num.end(), n) - num.begin() + 1;
}
int bit[int(1e6)];
void add(int x) {
	for( ; x <= num.size() + 10 ; x += x & -x)
		++ bit[x]; 
}
int ask(int x) {
	int r = 0;
	for( ; x ; x -= x & -x) r += bit[x];
	return r;
}

int main() {
	ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> t; -- t;
	num.push_back(0);
	for(int i = 1 ; i <= n ; ++ i) cin >> a[i], s[i] = s[i - 1] + a[i], num.push_back(s[i]), num.push_back(s[i] - t - 1);
	sort(num.begin(), num.end());
	add(get(0));
	ll ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		ans += i - ask(get(s[i] - t - 1));
		add(get(s[i]));
	}
	cout << ans << endl;
}
