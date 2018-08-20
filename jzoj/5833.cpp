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

typedef long long ll;

const int N = 4e5 + 10;

int n, m;

int head[N], rest[2 * N], to[2 * N], tot;

int sz[N], son[N], cnt[N];

int a[N], b[N];

int zui_duo_de_min_zu[N], min_zu_de_ren_shu[N];

int ans;

void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }

void dfs(int u, int fa) {
    sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}

void ins(int u) {
	cnt[a[u]] += b[u];
	int ct = cnt[a[u]];
	if(ans == 0 || cnt[ans] < ct || (cnt[ans] == ct && ans > a[u])) ans = a[u];
}

void push(int u, int fa, int type) {
	if(type == 0) ins(u);
	else cnt[a[u]] = 0;
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == fa) continue;
		push(v, u, type);
	}
}

void sol(int u, int fa) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == son[u] || v == fa) continue;
        sol(v, u);
        push(v, u, 1);
        ans = 0;
    }
    ans = 0;

	if(son[u]) sol(son[u], u);

	ins(u);
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == son[u] || v == fa) continue;
		push(v, u, 0);
	}

    zui_duo_de_min_zu[u] = ans;
	min_zu_de_ren_shu[u] = cnt[ans];
}

void read(int &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
//	freopen("data.in", "r", stdin);
	freopen("endless.in", "r", stdin);
	freopen("endless.out", "w", stdout);
    read(n), read(m);
    for(int i = 1, u, v ; i < n ; ++ i) {
		read(u), read(v);
		add(u, v), add(v, u);
	}
	for(int i = 1 ; i <= n ; ++ i) read(a[i]), read(b[i]);
	dfs(1, 0);
	sol(1, 0);
	for(int i = 1 ; i <= n ; ++ i) {
		printf("%d %d\n", zui_duo_de_min_zu[i], min_zu_de_ren_shu[i]);
	}
}
