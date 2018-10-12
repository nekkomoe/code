#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = (1 << 20) + 10;
int n, a[N];
struct T {
	int x, y;
	T(int x = 0, int y = 0) : x(x), y(y) { };
} f[N];
T operator + (T a, T b) {
	int mx = max(a.x, b.x);
	return (T) { mx, mx == a.x ? max(a.y, b.x) : max(a.x, b.y) };
}
void sol() {
	int len;
	memset(f, 0, sizeof f);
	scanf("%d", &len), n = 20;
	for(int i = 0 ; i < len ; ++ i) scanf("%d", &a[i]), f[a[i]] = f[a[i]] + T(a[i]);
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < (1 << n) ; ++ j) 
			if(!((j >> i) & 1))
				f[j] = f[j] + f[j ^ (1 << i)];
	ll ans = 0;
	for(int i = 0 ; i < (1 << 20) ; ++ i)
		ans = max(ans, 1ll * i * f[i].x * f[i].y);
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while(T --) sol();
}
