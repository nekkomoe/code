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
vector<pair<int, int> > g[N];
int n, S, E, ans = 0x3f3f3f3f;
int sz[N], f[N] = { 0x3f3f3f3f }, root, ban[N], size;

void getrt(int u, int fa) {
	sz[u] = 1, f[u] = 0;
	for(auto e: g[u]) {
		int v = e.first, w = e.second;
		if(ban[v] || v == fa) continue;
		getrt(v, u);
		sz[u] += sz[v], f[u] = max(f[u], sz[v]);
	}
	f[u] = max(f[u], size - sz[u]);
	if(f[u] < f[root]) root = u;
}

set<int> st;

void dfs(int u, int fa, int dep, int ty) {
	if(ty == 0) {
		if(S <= dep && dep <= E) ans = min(ans, dep);
		int mn = S - dep;
		if(st.size()) {
			int mx = * -- st.end();
			if(dep + mx >= S) {
				int y = dep + *st.lower_bound(S - dep);
				if(S <= y && y <= E) ans = min(ans, y);
			}
		}
	} else st.insert(dep);
	for(auto e: g[u]) {
		int v = e.first, w = e.second;
		if(ban[v] || v == fa) continue;
		dfs(v, u, dep + w, ty);
	}
}

void sol(int u) {
	ban[u] = 1;
	st.clear();
	st.insert(0);
	for(auto e: g[u]) {
		int v = e.first, w = e.second;
		if(ban[v]) continue;
		dfs(v, u, w, 0);
		dfs(v, u, w, 1);
	}
	for(auto e: g[u]) {
		int v = e.first, w = e.second;
		if(ban[v]) continue;
		root = 0, size = sz[v];
		getrt(v, 0), sol(root);
	}
}

int main() {
	scanf("%d%d%d", &n, &S, &E);
	for(int i = 1, u, v, w ; i < n ; ++ i) scanf("%d%d%d", &u, &v, &w), g[u].push_back( { v, w }), g[v].push_back( { u, w } );
	size = n, getrt(1, 0), sol(root);
	if(S <= 0 && 0 <= E) ans = min(ans, 0);
	printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
}
