#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, tot, ans[int(1e6) + 10];

inline void read(int &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

struct Tree {
	int ch[N][2], fa[N], root, dfn[N], pos[N], clk, vis[N];
	Tree() { vis[0] = 1; }
	void dfs(int u) {
		if(ch[u][0]) dfs(ch[u][0]);
		dfn[pos[u] = ++ clk] = u;
		if(ch[u][1]) dfs(ch[u][1]);
	}
	inline int rot(int u) {
//		cout << "rot in " << u << endl;
		ans[++ tot] = u;
		int f = fa[u], g = fa[f];
		if(g) ch[g][ch[g][1] == f] = u;
		fa[u] = g;
		int k = ch[f][1] == u;
		ch[f][k] = ch[u][!k];
		if(ch[u][!k]) fa[ch[u][!k]] = f;
		ch[u][!k] = f, fa[f] = u;
	}
	inline void splay(int u) {
//		printf("splay: %d\n", u);
		for(int f = fa[u] ; !vis[f] ; f = fa[u]) {
//			printf("fa[%d] = %d\n", u, fa[u]);
			int g = fa[f];
			if((ch[g][0] == f) == (ch[f][0] == u)) {
				if(!vis[g]) rot(f);
			} else {
				rot(u);
			}
			if(!vis[fa[u]]) rot(u);
		}
//		printf("splay end\n");
		vis[u] = 1;
	}
} xx, mz;

void dfs(int u) {
//	cout << "tot = " << tot << endl;
	if(!u) return ;
	xx.splay(xx.dfn[mz.pos[u]]);
	dfs(mz.ch[u][0]), dfs(mz.ch[u][1]);
}

int main() {
//	freopen("data.in", "r", stdin);
//	freopen("data.out", "w", stdout);
//	freopen("become.in", "r", stdin);
//	freopen("become.out", "w", stdout);
	read(n);
	for(int i = 1 ; i <= n ; ++ i) {
		read(xx.ch[i][0]), read(xx.ch[i][1]);
		if(xx.ch[i][0]) xx.fa[xx.ch[i][0]] = i;
		if(xx.ch[i][1]) xx.fa[xx.ch[i][1]] = i;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		read(mz.ch[i][0]), read(mz.ch[i][1]);
		if(mz.ch[i][0]) mz.fa[mz.ch[i][0]] = i;
		if(mz.ch[i][1]) mz.fa[mz.ch[i][1]] = i;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(!xx.fa[i]) xx.root = i;
		if(!mz.fa[i]) mz.root = i;
	}
	xx.dfs(xx.root), mz.dfs(mz.root), dfs(mz.root), printf("%d\n", tot);
	for(int i = 1 ; i <= tot ; ++ i) printf("%d\n", ans[i]);
}
