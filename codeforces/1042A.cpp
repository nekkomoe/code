#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, a[110];
int main() {
	cin >> n >> m;
	int mnk, mxk = m;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		mxk = max(mxk, a[i] + m);
	}
	sort(a + 1, a + 1 + n);
	ll sum = 0;
	for(int i = 1 ; i <= n ; ++ i) sum += a[n] - a[i];
	if(sum >= m) {
		mnk = a[n];
	} else {
		m -= sum;
		mnk = a[n] + m / n + (m % n != 0);
	}
	cout << mnk << ' ' << mxk << endl; 
}
