#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10, mod = 1e9 + 7;

int n, l[N], r[N];
vector<int> g[N];

struct BIT {
	ll sum[N];
	void addsig(int x, ll y) {
		for( ; x <= n ; x += x & -x)
			(sum[x] += y) %= mod;
	}
	void add(int l, int r, ll s) {
		addsig(l, s), addsig(r + 1, -s);
	}
	ll ask(int x) {
		ll r = 0;
		for( ; x ; x -= x & -x)
			(r += sum[x]) %= mod;
		return r;
	}
} a, b;

int dep[N];
void dfs(int u) {
	static int tot = 0;
	l[u] = ++ tot;
	for(int v: g[u])
		dep[v] = dep[u] + 1, dfs(v);
	r[u] = tot;
}

int main() {
	scanf("%d", &n);
	for(int i = 2, fa ; i <= n ; ++ i)
		scanf("%d", &fa), g[fa].push_back(i);
	dfs(1);
	int q; scanf("%d", &q);
	for(int i = 1, op, v, x, k ; i <= q ; ++ i) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d%d%d", &v, &x, &k);
			a.add(l[v], r[v], k % mod);
			b.add(l[v], r[v], (x + 1ll * dep[v] * k % mod) % mod);
		} else {
			scanf("%d", &v);
			ll qa = a.ask(l[v]);
			ll qb = b.ask(l[v]);
			ll ans = (1ll * -dep[v] * qa % mod + qb) % mod;
			ans = (ans % mod + mod) % mod;
			printf("%lld\n", ans);
		}
	}
}
