#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
map<int, int> g[N];
vector<int> mp[N];
int n, a[N], vis[N];
void dfs(int u, int fa) {
	for(int v: mp[u])
		if(v != fa)
			g[u][v] = 1, dfs(v, u);
}
void WA() {
	puts("No");
	exit(0);
}
int main() {
	cin >> n;
	for(int i = 1, u, v ; i < n ; ++ i) {
		cin >> u >> v;
		mp[u].push_back(v);
		mp[v].push_back(u);
	}
	dfs(1, 0);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	if(a[1] != 1) WA();
	queue<int> q;
	q.push(1);
	int p = 2;
	while(q.size()) {
		int u = q.front(); q.pop(); vis[u] = 1;
		while(p <= n && g[u].find(a[p]) != g[u].end()) {
			q.push(a[p]);
			++ p;
		}
	}
	for(int i = 1 ; i <= n ; ++ i) if(!vis[i]) WA();
	puts("Yes");
}
