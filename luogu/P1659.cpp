#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10, mod = 19930726;
int n, f[N], cnt[N]; char s[N]; ll k, ans = 1;

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

int main() {
	scanf("%d%lld%s", &n, &k, s + 1);
	for(int i = 1, mxr = 0, pos = 0 ; i <= n ; ++ i) {
		f[i] = i <= mxr ? min(f[2 * pos - i], mxr - i) : 0;
		while(i - f[i] > 1 && i + f[i] < n && s[i - f[i] - 1] == s[i + f[i] + 1]) ++ f[i];
		if(i + f[i] > mxr) mxr = i + f[i], pos = i;
		++ cnt[f[i] * 2 + 1];
	}
	for(int i = n ; i ; -- i) {
		if(cnt[i]) {
//			printf("cnt[%d] = %d\n", i, cnt[i]);
			ans = ans * pw(i, min((ll) cnt[i], k)) % mod;
			k -= cnt[i];
			cnt[i - 2] += cnt[i];
			if(k <= 0) break;
		}
	}
	printf("%lld\n", ans);
}
