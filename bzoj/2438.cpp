#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
vector<int> g[N], to[N];
int n, m, sz[N];
int cnt, bel[N];
int dfn[N], low[N], clk, ins[N];
stack<int> s;

void dfs(int u) {
	dfn[u] = low[u] = ++ clk;
	ins[u] = 1, s.push(u);
	for(int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		if(!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
		else if(ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		int v = ++ cnt;
		do {
			v = s.top(); s.pop(); ins[v] = 0;
			++ sz[cnt];
			bel[v] = cnt;
		} while(v != u);
	}
}

int deg[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v ; i <= m ; ++ i) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(!dfn[i]) {
			dfs(i);
		}
	}
	for(int u = 1 ; u <= n ; ++ u) {
		for(int i = 0 ; i < g[u].size() ; ++ i) {
			int v = g[u][i];
			if(bel[u] != bel[v]) {
				++ deg[bel[v]];
				to[bel[u]].push_back(bel[v]);
			}
		}
	}
	int ans = 0;
	for(int u = 1 ; u <= cnt ; ++ u) {
		if(deg[u] == 0) ++ ans;
	}
	for(int u = 1 ; u <= cnt ; ++ u) {
		if(deg[u] == 0 && sz[u] == 1) {
			int flag = 1;
			for(int i = 0 ; i < to[u].size() ; ++ i) {
				int v = to[u][i];
				if(deg[v] == 1) {
					flag = 0;
					break;
				}
			}
			if(flag) {
				-- ans;
				break;
			}
		}
	}
	printf("%.6lf\n", 1 - 1.0 * ans / n);
}
