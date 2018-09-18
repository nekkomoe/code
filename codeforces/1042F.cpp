#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
multiset<int> s[N];
int n, k; vector<int> g[N];
void dfs(int u, int fa, int dep) {
	if(g[u].size() == 1) return s[u].insert(dep), void();
	int c = 0; for(int v: g[u])
		if(v != fa)
			dfs(v, u, dep + 1),
			(c == 0 || s[c].size() < s[v].size() ? (c = v) : 0);
	swap(s[c], s[u]);
	for(int v: g[u])
		if(v != fa && v != c)
			for(int d: s[v]) {
				int x = k + 2 * dep - d;
				auto it = s[u].upper_bound(x);
				if(it == s[u].begin()) s[u].insert(d);
				else {
					int x = * -- it;
					s[u].erase(it);
					s[u].insert(max(x, d));
				}
			} 
}
int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> k;
	for(int i = 1, u, v ; i < n ; ++ i)
		cin >> u >> v,
		g[u].push_back(v),
		g[v].push_back(u);
	for(int i = 1 ; i <= n ; ++ i)
		if(g[i].size() >= 2)
			return dfs(i, 0, 0),
			printf("%d\n", int(s[i].size())), 0;
}
