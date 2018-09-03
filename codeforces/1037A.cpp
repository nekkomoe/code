#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, s, a[N];
ll ans;
int main() {
	cin >> n >> s;
	for(int i = 1 ; i <= n ; ++ i) cin >> a[i];
	sort(a + 1, a + 1 + n);
	for(int i = 1 ; i <= n / 2 ; ++ i) {
		if(a[i] > s) ans += a[i] - s;
		if(a[n - i + 1] < s) ans += s - a[n - i + 1];
	}
	ans += abs(a[n / 2 + 1] - s);
	printf("%lld\n", ans);
}
