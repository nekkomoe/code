#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100000 + 10;
vector<int> g[N];
int n, m, vis[N], ins[N], nxt[N], lst[N], flag, ans[N]; vector<int> s;
void WA() { puts("NIE"), exit(0); }
int tar;
void dfs(int u, int fa) {
	vis[u] = 1;
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v != fa) {
			if(vis[v]) {
				tar = v;
				ans[v] = u;
				flag = 1;
				return ;
			}
			dfs(v, u);
			if(flag) return ;
		}
	}
}
void sol(int u, int fa) {
	if(fa) ans[u] = fa;
	vis[u] = 2;
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(v != fa) {
			if(vis[v] != 2) {
				sol(v, u);
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v ; i <= m ; ++ i) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v), g[v].push_back(u);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(!vis[i]) {
			flag = 0;
			dfs(i, 0);
			if(!flag) WA();
			sol(tar, 0);
		}
	}
	puts("TAK");
}
