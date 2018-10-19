#include <bits/stdc++.h>
using namespace std;
int n, m;

bool check(int mid) {
	int x = mid / 2, y = mid / 3, z = mid / 6;
	return x >= n && y >= m && min(z, x - n) >= m - y + z;
}

int main() {
	scanf("%d%d", &n, &m);
	int l = 0, r = 1e9, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) {
			ans = mid, r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%d\n", ans);
} 
