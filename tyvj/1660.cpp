#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k, a[int(1e4) + 10]; vector<int> v[int(1e4) + 10];

void sol1() {
	ll sum = 0, ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		sum += a[i], ans += sum;
	printf("%.2lf\n", 1.0 * ans / n);
}

void sol2() {
	for(int i = 1, j = 1 ; i <= n ; ++ i) {
		v[j].push_back(a[i]);
		++ j;
		if(j > k) j = 1;
	}
	ll ans = 0;
	for(int i = 1 ; i <= k ; ++ i) {
		ll sum = 0;
		for(int j = 0 ; j < v[i].size() ; ++ j)
			sum += v[i][j], ans += sum;
	}
	printf("%.2lf\n", 1.0 * ans / n);
}

int main() {
	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) cin >> a[i];
	sort(a + 1, a + 1 + n);
	sol1();
	sol2();
}
