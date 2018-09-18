#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, a[N], t[N];
ll f[N], s[N], m;

int get(int x) {
	ll tot = 0;
	for(int i = 1 ; i <= n ; ++ i) t[i] = a[i];
	for(int i = 2 ; i <= n ; ++ i)
		if(t[i] - t[i - 1] > x)
			tot += t[i] - t[i - 1] - x,
			t[i] = t[i - 1] + x;
	for(int i = n - 1 ; i ; -- i)
		if(t[i] - t[i + 1] > x)
			tot += t[i] - t[i + 1] - x,
			t[i] = t[i + 1] + x;
	if(tot > m) return 0;
	for(int i = 1 ; i <= n ; ++ i)
		s[i] = s[i - 1] + t[i];
	for(int i = 1, j = 1 ; i <= n ; ++ i) {
		while(j < i && t[j] <= 1ll * (i - j) * x) ++ j;
		f[i] = s[i - 1] - s[j - 1] - 1ll * x * (i - j) * (i - j + 1) / 2;
	}
	for(int i = n, j = n ; i ; -- i) {
		while(j > i && t[j] <= 1ll * (j - i) * x) -- j;
		f[i] += s[j] - s[i] - 1ll * x * (j - i) * (j - i + 1) / 2;
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(tot + f[i] + t[i] <= m)
			return i;
	return 0;
}

int main() {
	scanf("%d%lld", &n, &m);
	int l = 0, r = 0;
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), r = max(r, a[i]);
	int ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(get(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d %d\n", get(ans), ans);
}
