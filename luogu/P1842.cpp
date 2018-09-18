#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50000 + 10;
int n; struct T { int w, s; } t[N];
bool operator < (T a, T b) { return a.w + a.s < b.w + b.s; }
int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) cin >> t[i].w >> t[i].s;
	sort(t + 1, t + 1 + n);
	int sum = t[1].w, ans = -t[1].s;
	for(int i = 2 ; i <= n ; ++ i) {
		ans = max(ans, sum - t[i].s); 
		sum += t[i].w;
	}
	cout << ans << endl;
}
