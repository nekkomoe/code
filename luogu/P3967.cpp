#include <bits/stdc++.h>
using namespace std;
const int N = 5010, M = 1e5 + 10, inf = 0x3f3f3f3f;
int head[N], rest[M], from[M], to[M], w[M], co[M], tot = 1, wbak[M], cobak[M];
void sig(int u, int v, int w, int co) {
	from[++ tot] = u, to[tot] = v, :: w[tot] = w, :: co[tot] = co, rest[tot] = head[u], head[u] = tot;
}
int a[110][110], n, m, s, t;
void add(int u, int v, int w, int co) {
	sig(u, v, w, co);
	if(1 <= u && u <= n && n + 1 <= v && v <= 2 * n)
		a[u][v - n] = tot;
	sig(v, u, 0, -co);
}
int ban[M];
int dis[N], inq[N], pre[N];
bool spfa() {
	for(int i = 1 ; i <= n ; ++ i) dis[i] = inf, pre[i] = 0;
	queue<int> q;
	q.push(s), inq[s] = 1, dis[s] = 0;
	while(q.size()) {
		int u = q.front(); q.pop(); inq[u] = 0;
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i], co = :: co[i];
			if(ban[i]) continue;
			if(w[i] && dis[v] > dis[u] + co) {
				dis[v] = dis[u] + co;
				pre[v] = i;
				if(!inq[v]) {
					q.push(v);
					inq[v] = 1;
				}
			}
		}
	}
	return dis[t] != inf;
}

pair<int, int> sol() {
	int mxf = 0, sum = 0;
	while(spfa()) {
		int mn = inf;
		for(int i = pre[t] ; i ; i = pre[from[i]]) {
			assert(!ban[i]);
			mn = min(mn, w[i]);
		}
		for(int i = pre[t] ; i ; i = pre[from[i]]) {
			assert(!ban[i]);
			w[i] -= mn;
			w[i ^ 1] += mn;
		}
		mxf += mn;
		sum += mn * dis[t];
	}
	return make_pair(mxf, sum);
}
int wfafa[M];
int main() {
	scanf("%d", &n);
	s = 2 * n + 1, t = s + 1;
	for(int i = 1 ; i <= n ; ++ i) {
		add(s, i, 1, 0);
		add(i + n, t, 1, 0);
		for(int j = 1 ; j <= n ; ++ j) {
			int h; scanf("%d", &h);
			add(i, j + n, 1, -h);
		}
	}

	int befn = n;
	n = t;
	for(int i = 1 ; i <= tot ; ++ i) wbak[i] = w[i], cobak[i] = co[i];
	pair<int, int> res = sol();
	for(int i = 1 ; i <= tot ; ++ i) wfafa[i] = w[i];
	printf("%d\n", -res.second);
	for(int i = 1 ; i <= befn ; ++ i) {
		for(int j = 1 ; j <= befn ; ++ j) {
			if(wfafa[a[i][j]]) continue;
			ban[a[i][j]] = ban[a[i][j] ^ 1] = 1;
			for(int k = 1 ; k <= tot ; ++ k) w[k] = wbak[k], co[k] = cobak[k];
			pair<int, int> t = sol();
			ban[a[i][j]] = ban[a[i][j] ^ 1] = 0;
//			assert(t.second >= res.second);
			if(t.second != res.second) {
				printf("%d %d\n", i, j);
				break;
			}
		}
	}
}
