#include <bits/stdc++.h>
using namespace std;
const int N = 10000 + 10, inf = 0x3f3f3f3f;

int id[N][12], cnt;
struct E { int v, w; };
vector<E> g[N * 12];

int n, m, k, s, t, dis[N * 12], vis[N * 12];

struct T { int u, w; }; bool operator < (T a, T b) { return a.w > b.w; }
priority_queue<T> pq;

int main() {
	cin >> n >> m >> k;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 0 ; j <= k ; ++ j)
			id[i][j] = ++ cnt;
	cin >> s >> t, ++ s, ++ t;
	for(int i = 1, u, v, w ; i <= m ; ++ i) {
		cin >> u >> v >> w;
		++ u, ++ v;
		for(int j = 0 ; j <= k ; ++ j) {
			g[id[u][j]].push_back((E) { id[v][j], w });
			g[id[v][j]].push_back((E) { id[u][j], w });
			if(j) {
				g[id[u][j]].push_back((E) { id[v][j - 1], 0 });
				g[id[v][j]].push_back((E) { id[u][j - 1], 0 });
			}
		}
	}
	memset(dis, 0x3f, sizeof dis);
	dis[id[s][k]] = 0; pq.push((T) { id[s][k], 0 });
	while(pq.size()) {
		int u = pq.top().u; pq.pop();
		if(vis[u]) continue; vis[u] = 1;
		for(int i = 0 ; i < g[u].size() ; ++ i) {
			int v = g[u][i].v, w = g[u][i].w;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push((T) { v, dis[v] });
			}
		}
	}
	int ans = inf;
	for(int j = 0 ; j <= k ; ++ j)
		ans = min(ans, dis[id[t][j]]);
	cout << ans << endl;
} 
