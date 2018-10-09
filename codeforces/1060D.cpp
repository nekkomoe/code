#include <bits/stdc++.h>
using namespace std;

int main() {
	ios :: sync_with_stdio(0);
	int n; cin >> n;
	vector<int> a, b;
	for(int i = 1, x, y ; i <= n ; ++ i) cin >> x >> y, a.push_back(x), b.push_back(y);
	sort(a.begin(), a.end()), sort(b.begin(), b.end());
	long long ans = n;
	for(int i = 0 ; i < n ; ++ i) ans += max(a[i], b[i]);
	cout << ans << endl;
}