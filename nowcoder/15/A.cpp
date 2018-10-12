#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10;
vector<int> g[N]; int n; ll ans;
ll cnt[N][2];

void get(int u, int fa) {
	cnt[u][0] = 1;
	for(int v: g[u])
		if(v != fa) {
			get(v, u);
			ll c0 = cnt[v][1], c1 = cnt[v][0];
			ans += c0 * cnt[u][0] + c1 * cnt[u][1];
			cnt[u][0] += c0;
			cnt[u][1] += c1;
		}
}

int main() {
	scanf("%d", &n);
	for(int i = 1, u, v ; i < n ; ++ i)
		scanf("%d%d", &u, &v),
		g[u].push_back(v),
		g[v].push_back(u);
	get(1, 0);
	printf("%lld\n", ans);
}
