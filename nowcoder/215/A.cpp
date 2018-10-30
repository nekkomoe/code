#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 2e5 + 10;
int cnt[N]; ll ans;

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, x ; i <= n ; ++ i) {
		scanf("%d", &x);
		for(ll j = 1 ; j * j <= int(2e5) ; ++ j)
			if(j * j >= x)
				ans += cnt[j * j - x];
		++ cnt[x];
	}
	printf("%lld\n", ans);
}
