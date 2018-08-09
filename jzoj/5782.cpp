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

const int N = 1e5 + 10;

int dep[N], fa[N], w[N];

int n, m, q, dis[N];

vector<int> G[N];

__attribute__((always_inline)) __attribute__((optimize("O2"))) __attribute__((optimize("O3"))) __inline int get(int x) { return x == fa[x] ? x : get(fa[x]); }

__attribute__((always_inline)) __attribute__((optimize("O2"))) __attribute__((optimize("O3"))) __inline int merge(int x, int y, int day) {
	if(dep[x] > dep[y]) swap(x, y);
	fa[x] = y, w[x] = day, G[y].push_back(x);
	if(dep[x] == dep[y]) ++ dep[y];
}

__attribute__((always_inline)) __attribute__((optimize("O2"))) __attribute__((optimize("O3"))) __inline void dfs(int u) {
	dis[u] = dis[fa[u]] + 1;
	for(int v: G[u]) dfs(v);
}

template<typename T> __attribute__((always_inline)) __attribute__((optimize("O2"))) __attribute__((optimize("O3"))) __inline void read(T &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

__attribute__((optimize("O2"))) __attribute__((optimize("O3"))) int main() {
	freopen("pictionary.in", "r", stdin), freopen("pictionary.out", "w", stdout), read(n), read(m), read(q), iota(fa + 1, fa + 1 + n, 1);
	for(register int i = 1 ; i <= m ; ++ i)
		for(register int x = m - i + 1, j = x ; j + x <= n ; j += x) {
			register int u = get(j), v = get(j + x);
			if(u != v) merge(u, v, i);
		}
	for(register int i = 1 ; i <= n ; ++ i) if(fa[i] == i) { dfs(i), fa[i] = 0; break; }
	for(register int i = 1, u, v ; i <= q ; ++ i) {
		read(u), read(v);
		int ans = 0;
		if(dis[u] < dis[v]) swap(u, v);
		while(dis[fa[u]] >= dis[v]) ans = max(ans, w[u]), u = fa[u];
		if(u != v) {
			while(fa[u] != fa[v]) ans = max(ans, max(w[u], w[v])), u = fa[u], v = fa[v];
			ans = max(ans, max(w[u], w[v]));
		}
		printf("%d\n", ans);
	}
}
