#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 3e5 + 10;
int n, fa[N][21], dfn[N], rig[N], dep[N];
vector<int> g[N];

void dfs(int u) {
	dfn[u] = ++ dfn[0];
	dep[u] = dep[fa[u][0]] + 1;
	for(int i = 1 ; i <= 20 ; ++ i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(int v: g[u])
		if(v != fa[u][0])
			fa[v][0] = u,
			dfs(v);
	rig[u] = dfn[0];
}

bool cmp(int a, int b) { return dfn[a] < dfn[b]; }

int getlca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 20 ; ~ i ; -- i)
		if(dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	if(u == v) return u;
	for(int i = 20 ; ~ i ; -- i)
		if(fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int m, k, a[N];

namespace VT {
	vector<int> toc;
	struct E { int v, w; };
	vector<E> g[N];
	int mxdis, pts, frst;
	void add(int u, int v, int w) {
		toc.push_back(u), toc.push_back(v);
		g[u].push_back((E) { v, w }), g[v].push_back((E) { u, w });
	}
	void clear() {
		for(int x: toc)
			g[x].clear();
	}
	void dfs(int u, int fa, int len) {
		if(len > mxdis) mxdis = len, pts = u;
		for(E e: g[u]) {
			int v = e.v, w = e.w;
			if(v != fa) {
				dfs(v, u, len + w);
			}
		}
	}
	void sol() {
		mxdis = 0, pts = frst, dfs(frst, 0, 0);
		mxdis = 0, dfs(pts, 0, 0);
		printf("%d\n", (mxdis + 1) / 2);
		clear();
	}
};

int sta[N];
bool fafa(int a, int b) { return dep[a] < dep[b]; }
void sol() {
//	vector<int> pts;
//	for(int i = 1 ; i <= k ; ++ i) pts.push_back(a[i]);
//	sort(pts.begin(), pts.end(), cmp);
//	pts.erase(unique(pts.begin(), pts.end()), pts.end());
//	for(int i = pts.size() - 1 ; i >= 1 ; -- i) pts.push_back(getlca(pts[i], pts[i - 1]));
//	sort(pts.begin(), pts.end(), cmp);
//	pts.erase(unique(pts.begin(), pts.end()), pts.end());
//	int top = 0;
//	for(int x: pts) {
//		while(top && dfn[x] > rig[sta[top]]) -- top;
//		if(top) VT :: add(sta[top], x, dep[x] - dep[sta[top]]);
//		sta[++ top] = x;
//	}
//	VT :: frst = pts[0];
//	VT :: sol();
	sort(a + 1, a + 1 + k, fafa);
	int mx = 0;
	for(int i = 1 ; i < k ; ++ i)
		mx = max(mx, dep[a[k]] + dep[a[i]] - 2 * dep[getlca(a[i], a[k])]);
	printf("%d\n", (mx + 1) / 2);
}

int main() {
	scanf("%d", &n);
	for(int i = 1, u, v ; i < n ; ++ i)
		scanf("%d%d", &u, &v),
		g[u].push_back(v),
		g[v].push_back(u);
	dfs(1);
	scanf("%d", &m);
	for(int i = 1 ; i <= m ; ++ i) {
		scanf("%d", &k);
		for(int j = 1 ; j <= k ; ++ j) scanf("%d", &a[j]);
		sol();
	}
}
