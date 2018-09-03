#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct E { int u, v, time; } e[N];
int deg[N], ans[N], inq[N], n, m, k;
set<pair<int, int> > s;
vector<pair<int, int> > g[N];

int main() {
	cin >> n >> m >> k;
	for(int i = 1 ; i <= m ; ++ i) {
		int u, v, time = i;
		cin >> u >> v;
		e[i] = (E) { u, v, time };
		g[u].push_back(make_pair(v, time)), g[v].push_back(make_pair(u, time));
		++ deg[u], ++ deg[v];
	}
	for(int i = 1 ; i <= n ; ++ i) s.insert(make_pair(deg[i], i)), inq[i] = 1;
	while(s.size() && s.begin() -> first < k) {
		int u = s.begin() -> second; s.erase(s.begin());
		inq[u] = 0;
		for(auto e: g[u]) {
			int v = e.first;
			if(inq[v]) {
				s.erase(make_pair(deg[v], v));
				-- deg[v];
				s.insert(make_pair(deg[v], v));
			}
		}
	}
	for(int i = m - 1 ; ~ i ; -- i) {
		ans[i] = s.size();
		int u = e[i + 1].u, v = e[i + 1].v;
		if(inq[u] && inq[v]) {
			s.erase(make_pair(deg[u], u));
			s.erase(make_pair(deg[v], v));
			-- deg[u], -- deg[v];
			s.insert(make_pair(deg[u], u));
			s.insert(make_pair(deg[v], v));
		}
		while(s.size() && s.begin() -> first < k) {
			int u = s.begin() -> second; s.erase(s.begin());
			inq[u] = 0;
			for(auto e: g[u]) {
				int v = e.first, time = e.second;
				if(time <= i && inq[v]) {
					s.erase(make_pair(deg[v], v));
					-- deg[v];
					s.insert(make_pair(deg[v], v));
				}
			}
		}
	}
	for(int i = 0 ; i < m ; ++ i) cout << ans[i] << endl;
}
