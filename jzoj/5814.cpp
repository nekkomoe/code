%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, p = 1e9 + 7;
typedef long long ll;
vector<int> g[N];
int fa[N][21], dep[N], n, q;

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
	return r;
}

ll inv(ll a) { return pw(a, p - 2); }

ll f[N]; 	// 从u回到fa[u]的期望步数

ll h[N];

void dfs(int u) {
	dep[u] = dep[fa[u][0]] + 1;
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v == fa[u][0]) continue;
		fa[v][0] = u;
		dfs(v);
	}
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v == fa[u][0]) continue;
		f[u] = (f[u] + f[v] + 1) % p;
	}
	f[u] = (f[u] + 1) % p;
}

void dfs2(int u) {
	int fa = :: fa[u][0], deg = g[fa].size();
	ll sum = 0;
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v == fa) sum = (sum + h[u] + 1) % p;
		else sum = (sum + f[v] + 1) % p;
	}
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v != fa) h[v] = (sum - f[v]) % p, dfs2(v);
	}
}

void dfs3(int u) {
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v == fa[u][0]) continue;
		f[v] = (f[v] + f[u]) % p;
		h[v] = (h[v] + h[u]) % p;
		dfs3(v);
	}
}

int getlca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

ll sol(int u, int v) {
	ll res = 0;
	int d = getlca(u, v);
	res += (f[u] - f[d]) % p;
	res %= p;
	res += (h[v] - h[d]) % p;
	res %= p;
	return (res % p + p) % p;
}

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for(int i = 1, u, v ; i < n ; ++ i) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1);
	f[1] = h[1] = 0;
	dfs2(1);
	dfs3(1);
	for(int j = 1 ; j <= 20 ; ++ j)
		for(int i = 1 ; i <= n ; ++ i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	for(int i = 1, u, v ; i <= q ; ++ i) {
		scanf("%d%d", &u, &v);
		printf("%lld\n", sol(u, v));
	}
}
