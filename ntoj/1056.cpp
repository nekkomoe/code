#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<pair<int, int> > g[N];

void add(int u, int v, int w) {
	g[u].push_back(make_pair(v, w));
}

int inq[N], n, m, dis[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, T, a, b ; i <= m ; ++ i) {
		scanf("%d%d%d", &T, &a, &b);
		if(T == 1) {
			add(a, b, 0), add(b, a, 0);
		} else if(T == 2) {
			add(a, b, 1);
		} else if(T == 3) {
			add(b, a, 0);
		} else if(T == 4) {
			add(b, a, 1);
		} else if(T == 5) {
			add(a, b, 0);
		}
	}
	queue<int> q;
	for(int i = 1 ; i <= n ; ++ i) dis[i] = 1, q.push(i);
	while(q.size()) {
		int u = q.front(); q.pop(); inq[u] = 0;
		for(int i = 0 ; i < g[u].size() ; ++ i) {
			int v = g[u][i].first, w = g[u][i].second;
			if(dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) ans += dis[i];
	printf("%d\n", ans);
}
