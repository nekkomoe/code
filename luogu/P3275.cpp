#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100000 + 10;
int n, k, S, cnt[N], inq[N], dis[N];
struct E { int v, w; };
vector<E> g[N]; queue<int> q;
void add(int u, int v, int w) {
	g[u].push_back((E) { v, w });
}
int main() {
	scanf("%d%d", &n, &k), S = n + 1;
	
	for(int i = 1 ; i <= n ; ++ i) {
		add(S, i, 1);
	}
	
	for(int i = 1, op, a, b ; i <= k ; ++ i) {
		scanf("%d%d%d", &op, &a, &b);
		if(op == 1) {
			add(b, a, 0), add(a, b, 0);
		} else if(op == 2) {
			if(a == b) return puts("-1"), 0;
			add(a, b, 1);
		} else if(op == 3) {
			add(b, a, 0);
		} else if(op == 4) {
			if(a == b) return puts("-1"), 0;
			add(b, a, 1);
		} else {
			add(a, b, 0);
		}
	}
	
	memset(dis, 0xcf, sizeof dis);
	q.push(S), inq[S] = 1, dis[S] = 0;
	while(q.size()) {
		int u = q.front(); q.pop(); inq[u] = 0;
		for(E e: g[u]) {
			int v = e.v, w = e.w;
			if(dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if(++ cnt[v] > n) return puts("-1"), 0;
				if(!inq[v]) {
					q.push(v), inq[v] = 1;
				}
			}
		}
	}
	
	ll ans = 0;
	for(int i = 1 ; i <= n ; ++ i) ans += dis[i];
	printf("%lld\n", ans);
} 
