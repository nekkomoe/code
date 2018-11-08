#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, m, a[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		if(m - a[i] >= 0) {
			m -= a[i];
			++ ans;
		} else {
			a[i] = m, m = 0;
			break;
		}
	}
	if(m) -- ans;
	printf("%d\n", ans);
}
