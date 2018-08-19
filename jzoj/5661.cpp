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
const int N = 5e3 + 10, P = 1e4 + 10;

int n, p, f[N][P];

int w[N], val[N], cnt, dfn[N], sz[N];

int head[N], rest[N * 2], to[N * 2], tot;

void add(int u, int v) {
	to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u) {
	sz[u] = 1;
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		dfs(v);
		sz[u] += sz[v];
	}
	dfn[++ cnt] = u;
}

int main() {
	freopen("medicine.in", "r", stdin);
	freopen("medicine.out", "w", stdout);
	scanf("%d%d", &n, &p);
	for(int i = 1 ; i <= n ; ++ i) {
		int f;
		scanf("%d%d%d", &w[i], &f, &val[i]);
		if(i != 1) add(f, i);
	}
	dfs(1);
	for(int i = 1 ; i <= n ; ++ i) {
		int u = dfn[i];
		for(int j = 0 ; j <= p ; ++ j) {
			int x = 0, y = 0;
			x = f[i - sz[u]][j];
			if(j - w[u] >= 0) y = f[i - 1][j - w[u]] + val[u];
			f[i][j] = max(x, y);
		}
	}
	printf("%d\n", f[n][p]);
}
