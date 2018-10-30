#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
int n, fa[N]; int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
vector<int> g[N]; int tag[N], vis[N], sz[N];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= 2 * n ; ++ i) fa[i] = i, sz[i] = 1;
	long long ans = 1;
	for(int i = 1, u, v ; i <= n ; ++ i) {
		scanf("%d%d", &u, &v);
		if(u == v) vis[u] = 1;
		u = get(u), v = get(v);
		if(u != v) {
			fa[u] = v;
			vis[v] |= vis[u];
			sz[v] += sz[u];
			sz[u] = 0;
		} else {
			tag[u] = 1;
		}
	}
	for(int i = 1 ; i <= 2 * n ; ++ i)
		if(fa[i] == i && !vis[i])
			ans = ans * (tag[i] ? 2 : sz[i]) % mod;
	printf("%lld\n", ans);
}
