#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int n, a[N]; ll s[N], s2[N];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), s[i] = s[i - 1] + a[i], s2[i] = s2[i - 1] + 1ll * a[i] * a[i];
	for(int i = 1 ; i <= n ; ++ i) {
		ll s = :: s[n] - a[i];
		ll s2 = :: s2[n] - 1ll * a[i] * a[i];
		int m = n - 1;
		ll T = m * s2 - s * s;
		if(i > 1) putchar(' ');
		printf("%lld", T);
	}
	puts("");
}
