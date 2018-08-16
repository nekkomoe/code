#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;

int sz[N], f[N] = { 0x3f3f3f3f }, root, sizeses, ban[N];
struct E { int to, w; };
vector<E> g[N];

void getsz(int u, int fa) {
	sz[u] = 1, f[u] = 0;
	for(auto e: g[u]) {
		int v = e.to;
		if(ban[v] || v == fa) continue;
		getsz(v, u);
		sz[u] += sz[v];
		f[u] = max(f[u], sz[v]);
	}
	f[u] = max(f[u], sizeses - sz[u]);
	if(f[u] < f[root]) root = u;
}

map<int, int> cnt;

int pw(int a, int b) {
	int r = 1;
	for( ; b ; b /= 2, a = 1ll * a * a % m) if(b % 2 == 1) r = 1ll * r * a % m;
	return r % m;
}

int inv[N], fac[N];

long long ans;

int getphi(int x) {
	int r = x;
	for(int i = 2 ; 1ll * i * i <= x ; ++ i) {
		if(x % i == 0) r = r / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x > 1) r = r / x * (x - 1);
	return r;
}

void dfs(int u, int fa, int len, int type, int dep, int fafa) {
	
	if(fafa == 1) {
		ans += len == 0;
	}
	
	if(type == 0) {
		int x = - len; x = (x % m + m) % m;
		int val = 1ll * x * inv[dep] % m;
		ans += cnt[val];
	} else {
		++ cnt[len];
	}
	
	for(auto e: g[u]) {
		int v = e.to;
		if(ban[v] || v == fa) continue;
		if(type == 0)
			dfs(v, u, (1ll * len * 10 + e.w) % m, type, dep + 1, fafa);
		else 
			dfs(v, u, (1ll * len + 1ll * e.w * fac[dep]) % m, type, dep + 1, fafa);
	}
}

void sol(int u) {
	ban[u] = 1;
	for(int fafa = 1 ; fafa <= 2 ; ++ fafa) {
		cnt.clear();
		for(auto e: g[u]) {
			int v = e.to;
			if(ban[v]) continue;
			dfs(v, u, e.w % m, 0, 1, fafa);
			dfs(v, u, e.w % m, 1, 1, fafa);
		}
		
		reverse(g[u].begin(), g[u].end());
	}
	for(auto e: g[u]) {
		int v = e.to;
		if(ban[v]) continue;
		root = 0, sizeses = sz[v], getsz(v, 0);
		sol(root);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	
	int p = getphi(m);
	inv[0] = 1, fac[0] = 1;
	for(int i = 1 ; i <= n ; ++ i) fac[i] = 1ll * fac[i - 1] * 10 % m, inv[i] = pw(fac[i], p - 1);
	for(int i = 1, u, v, w ; i < n ; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		++ u, ++ v, w %= m;
		g[u].push_back((E) { v, w });
		g[v].push_back((E) { u, w });
	}
	sizeses = n, root = 0, getsz(1, 0);
	sol(root);
	printf("%lld\n", ans);
}
