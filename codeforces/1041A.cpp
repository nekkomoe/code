#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, ans, mn = -1, mx = -1, x;
int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> x;
		if(mn == -1) mn = x;
		if(mx == -1) mx = x;
		mn = min(mn, x);
		mx = max(mx, x);
	}
	cout << (mx - mn + 1 - n) << endl;
}
