#include <bits/stdc++.h>
using namespace std;
const int N = 100000 + 10, inf = 1e9 + 10;
struct E { int v, w; };
int head[N], rest[N * 4], from[N * 4], to[N * 4], w[N * 4], tot;
void add(int u, int v, int w) {
	from[++ tot] = u, to[tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}
int n, m;
int dis[2][N], vis[N];
struct T { int u, w; }; bool operator < (T a, T b) { return a.w > b.w; }
priority_queue<T> pq;

void dij(int s, int *dis) {
	for(int i = 1 ; i <= n ; ++ i) dis[i] = inf, vis[i] = 0;
	pq.push((T) { s, 0 }), dis[s] = 0;
	while(pq.size()) {
		int u = pq.top().u; pq.pop();
		if(vis[u]) continue; vis[u] = 1;
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i], w = :: w[i];
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push((T) { v, dis[v] });
			}
		}
	}
}

int sta[N], rev[N], sz, l[N], r[N], ban[N * 4];

void getsta() {
	int u = 1;
	while(u != n) {
		sta[++ sz] = u, rev[u] = sz;
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i], w = :: w[i];
			if(dis[1][u] == dis[1][v] + w) {
				ban[i] = 1;
				u = v;
				break;
			}
		}
	}
	sta[++ sz] = n, rev[n] = sz;
}

void bfs(int S, int *dis, int *pos) {
	queue<int> q;
	q.push(sta[S]);
	pos[sta[S]] = S;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i], w = :: w[i];
			if(dis[v] == dis[u] + w && !rev[v] && !pos[v]) {
				pos[v] = S;
				q.push(v);
			}
		}
	}
}

int mn[N * 4], fa[N * 4];

int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }

struct Q {
	int l, r, w;
};
bool operator < (Q a, Q b) { return a.w < b.w; }
vector<Q> pl;

int main() {
//	freopen("boss.in", "r", stdin);
//	freopen("boss.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w ; i <= m ; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	dij(1, dis[0]), dij(n, dis[1]);
	getsta();
	
	
	
	for(int i = 1 ; i <= sz ; ++ i)
		bfs(i, dis[0], l);
	for(int i = sz ; i ; -- i)
		bfs(i, dis[1], r);
	
//	cout << "sz = " << sz << endl;
//	for(int i = 1 ; i <= sz ; ++ i)
//		printf("sta[%d] = %d, rev = %d\n", i, sta[i], rev[sta[i]]);
//	for(int i = 1 ; i <= n ; ++ i)
//		printf("%d: [%d, %d]\n", i, l[i], r[i]);
	
	for(int i = 1 ; i <= sz ; ++ i) mn[i] = inf;
	for(int i = 1 ; i <= tot ; ++ i) {
//		printf("%d %d->%d [%d, %d]: %d\n", ban[i], from[i], to[i], l[from[i]], r[to[i]], w[i]);
		if(ban[i]) continue;
		int u = from[i], v = to[i];
		int l = :: l[u], r = :: r[v];
		if(l && r && l < r) {
//			printf("modify: [%d, %d]: %d\n", l, r, dis[0][u] + w[i] + dis[1][v]);
//			for(int j = l ; j < r ; ++ j) {
//				mn[j] = min(mn[j], dis[0][u] + w[i] + dis[1][v]);
//			}
			pl.push_back((Q) { l, r - 1, dis[0][u] + w[i] + dis[1][v] });
		}
	}
	for(int i = 1 ; i <= sz + 1 ; ++ i) fa[i] = i;
	sort(pl.begin(), pl.end());
	for(int i = 0 ; i < pl.size() ; ++ i) {
		int l = pl[i].l, r = pl[i].r, w = pl[i].w;
		l = get(l);
		while(l <= r) {
			mn[l] = min(mn[l], w);
			fa[get(l)] = get(r);
			l = get(l + 1);
		}
	}
	int ans = dis[0][n], cnt = 0;
	for(int i = 1 ; i < sz ; ++ i)
		if(mn[i] != inf) {
			if(mn[i] == ans) {
				++ cnt;
			} else if(mn[i] > ans) {
				ans = mn[i];
				cnt = 1;
			}
		}
	cnt = ans == dis[0][n] ? m : cnt;
	printf("%d %d\n", ans, cnt);
}
