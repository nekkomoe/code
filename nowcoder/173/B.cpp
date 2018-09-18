#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, mod = 1e9 + 7;
int n, a[N * 2], s[N], top, pre[N]; ll f[N], sum[N];
int main() {
	scanf("%d", &n);
	int id = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &a[i]), a[i + n] = a[i];
		if(a[i] < a[id]) id = i;
	}
	for(int i = 1 ; i <= n ; ++ i) a[i] = a[id + i - 1];
	for(int i = 1 ; i <= n ; ++ i) {
		while(top && a[s[top]] > a[i]) -- top;
		pre[i] = s[top], s[++ top] = i;
	}
	sum[0] = f[0] = 1, f[1] = a[1], sum[1] = sum[0] - f[1];
	for(int i = 2 ; i <= n ; ++ i) {
		int sig = (i + pre[i] + 1) & 1 ? 1 : -1;
		f[i] = f[pre[i]] * sig;
		sig = i & 1 ? 1 : -1;
		f[i] = (f[i] + sig * (sum[i - 1] - sum[pre[i] - 1]) * a[i] % mod) % mod;
		sum[i] = (sum[i - 1] - sig * f[i]) % mod;
	}
	ll ans = 0;
	for(int i = n ; i >= 2 ; -- i) {
		int sig = (n - i) & 1 ? -1 : 1;
		ans = (ans + sig * f[i]) % mod;
	}
	ans = (ans % mod + mod) % mod;
	printf("%lld\n", ans);
}
