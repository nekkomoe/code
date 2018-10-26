#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 2e5 + 10;
int n, m, k, a[N];

bool check(int l, int r) {
	int tot = m, rst = 0;
	for(int i = l ; i <= r ; ++ i) {
		if(a[i] > rst) -- tot, rst = k;
		if(a[i] > rst) return 0;
		rst -= a[i];
		if(tot < 0) return 0;
	}
	return tot >= 0;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	int l = 0 , r = n, ans = 0;
//	for(int i = 1 ; i <= n ; ++ i) printf("%d ", check(i, n));
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid + 1, n)) ans = n - mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
}
