#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;

int n, m, d[N][N], nxt[N][N], vis[N], deg[N];
vector<int> g[N];
double f[N][N];

void spfa(int s, int *d) {
	for(int i = 1 ; i <= n ; ++ i) d[i] = 0x3f3f3f3f;
	queue<int> q;
	q.push(s), d[s] = 0, vis[s] = 1;
	while(q.size()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		for(int i = 0 ; i < g[u].size() ; ++ i) {
			int v = g[u][i];
			if(d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				if(!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
}

double dfs(int u, int v) {
//	cout << "u = " << u << " v = " << v << endl;
//	cout << "dis = " << d[u][v] << endl; 
	if(u == v) return f[u][v] = 0;
	if(d[u][v] <= 2) return f[u][v] = 1;
	if(f[u][v] != -1) return f[u][v];
	double t = 0;
	for(int i = 0 ; i < g[v].size() ; ++ i) {
		int x = g[v][i];
		t += dfs(nxt[nxt[u][v]][v], x);
	}
	t += dfs(nxt[nxt[u][v]][v], v);
	return f[u][v] = t / (deg[v] + 1) + 1;
}

int main() {
	int s, t; scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1, u, v ; i <= m ; ++ i)
		scanf("%d%d", &u, &v),
		g[u].push_back(v),
		g[v].push_back(u),
		++ deg[u],
		++ deg[v];
	for(int i = 1 ; i <= n ; ++ i) {
		spfa(i, d[i]);
		for(int j = 1 ; j <= n ; ++ j)
			f[i][j] = -1;
	}
	memset(nxt, 0x3f, sizeof nxt);
	for(int i = 1 ; i <= n ; ++ i)
		for(int t = 0 ; t < g[i].size() ; ++ t) {
			int x = g[i][t];
			for(int j = 1 ; j <= n ; ++ j)
				if(1 + d[x][j] == d[i][j])
					nxt[i][j] = min(nxt[i][j], x);
			}
//	for(int i = 1 ; i <= n ; ++ i, cout << endl)
//		for(int j = 1 ; j <= n ; ++ j)
//			cout << nxt[i][j] << ' ';
	printf("%.3lf\n", dfs(s, t));
}
