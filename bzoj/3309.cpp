#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e7 + 10;

ll f[N], g[N];
int pri[N], tot, mu[N]; bool vis[N];
int cnt[N], pro[N];

void init() {
	int n = 1e7;
	g[1] = 0;
	for(int i = 2 ; i <= n ; ++ i) {
		if(!vis[i]) {
			pri[++ tot] = i;
			cnt[i] = 1;
			pro[i] = i;
			g[i] = 1;
		}
		for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
			int x = i, p = pri[j];
			vis[x * p] = 1;
			if(x % p == 0) {
				cnt[x * p] = cnt[x] + 1;
				pro[x * p] = pro[x] * p;
				mu[x * p] = 0;
				if(x == pro[x]) g[x * p] = 1;
				else g[x * p] = cnt[x / pro[x]] == cnt[x * p] ? -g[x / pro[x]] : 0;
				break;
			} else {
				cnt[x * p] = 1;
				pro[x * p] = p;
				g[x * p] = cnt[x] == 1 ? -g[x] : 0;
			} 
		}
	}
	for(int i = 2 ; i <= n ; ++ i) g[i] += g[i - 1];
}

int main() {
//	freopen("data.in", "r", stdin);
	init();
	int T; scanf("%d", &T);
	while(T --) {
		int a, b; scanf("%d%d", &a, &b);
		if(a > b) swap(a, b);
		ll ans = 0;
		for(ll i = 1, j ; i <= a ; i = j + 1) {
			j = min(a / (a / i), b / (b / i));
			ans += (a / i) * (b / i) * (g[j] - g[i - 1]);
		}
		printf("%lld\n", ans);
	}
}
