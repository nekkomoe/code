#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void sol() {
	static int tot = 0; ++ tot;
	int n, m, k; scanf("%d%d%d", &n, &m, &k);
	
	double ans = 0;
	ll all = 1ll * n * m * n * m;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j) {
			ll sum = 0;
			sum += 1ll * (i - 1) * m * (i - 1) * m;
			sum += 1ll * (n - i) * m * (n - i) * m;
			sum += 1ll * n * (j - 1) * n * (j - 1);
			sum += 1ll * n * (m - j) * n * (m - j);
			sum -= 1ll * (i - 1) * (j - 1) * (i - 1) * (j - 1);
			sum -= 1ll * (n - i) * (m - j) * (n - i) * (m - j);
			sum -= 1ll * (i - 1) * (m - j) * (i - 1) * (m - j);
			sum -= 1ll * (n - i) * (j - 1) * (n - i) * (j - 1);
			
			double p = pow(1.0 * sum / all, k);
			ans += 1 - p;
		}
	printf("Case #%d: %d\n", tot, (int) round(ans));
}

int main() {
	int T; scanf("%d", &T);
	while(T --) sol();
}
