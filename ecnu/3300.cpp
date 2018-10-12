#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 2e5 + 10;

int n, t[N]; ll a[N];

void sol() {
	scanf("%d", &n);
	memset(a, 0, sizeof a);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &t[i]), ++ a[t[i]];
	for(int i = 0 ; i < 17 ; ++ i)
		for(int j = 0 ; j < (1 << 17) ; ++ j)
			if((j >> i) & 1)
				a[j] += a[j ^ (1 << i)];
	ll ans = 0;
	for(int i = 1 ; i <= n ; ++ i) ans += a[t[i]];
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while(T --) sol();
}
