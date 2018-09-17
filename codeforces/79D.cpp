#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10000 + 10, M = 5e6 + 10;
int dis[N], n, k, l, head[N], rest[M], to[M], tot, w[1000][1000], id[M], a[M], len[M];
void add_sig(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }
void add(int u, int v) { add_sig(u, v), add_sig(v, u); }
void bfs(int s) {
	for(int i = 0 ; i <= n ; ++ i) dis[i] = 0x3f3f3f3f;
	queue<int> q;
	q.push(s), dis[s] = 0;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i];
			if(dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1, q.push(v); 
			}
		}
	}
} 

int f[M];

int main() {
	scanf("%d%d%d", &n, &k, &l);
	for(int i = 1, pos ; i <= k ; ++ i) scanf("%d", &pos), a[pos] = 1;
	for(int i = 0 ; i <= n ; ++ i) {
		a[i] = a[i] != a[i + 1];
		if(a[i] == 1) id[i] = ++ id[n + 1];
	}
	for(int i = 1 ; i <= l ; ++ i) scanf("%d", &len[i]);
	for(int i = 0 ; i <= n ; ++ i)
		for(int j = 1 ; j <= l ; ++ j) {
			if(i - len[j] >= 0 && a[i - len[j]] == 0) add(i - len[j], i);
			if(i + len[j] <= n) add(i, i + len[j]);
		}
	for(int i = 0 ; i <= id[n + 1] ; ++ i)
		for(int j = 0 ; j <= id[n + 1] ; ++ j)
			w[i][j] = 0x3f3f3f3f;
	for(int i = 0 ; i <= n ; ++ i)
		if(id[i]) {
			bfs(i);
			for(int j = 0 ; j <= n ; ++ j)
				if(id[j])
					w[id[i]][id[j]] = dis[j];
		} 
	k = id[n + 1];
	for(int s = 0 ; s < (1 << k) ; ++ s) f[s] = 0x3f3f3f3f;
	f[0] = 0; 
	for(int s = 1 ; s < (1 << k) ; ++ s) {
		for(int i = 0 ; i < k ; ++ i)
			if((s >> i) & 1) {
				for(int j = i + 1 ; j < k ; ++ j)
					if((s >> j) & 1)
						f[s] = min(f[s], f[s - (1 << i) - (1 << j)] + w[i + 1][j + 1]);
				break;
			}
	}
	if(f[(1 << k) - 1] == 0x3f3f3f3f) puts("-1");
	else printf("%d\n", f[(1 << k) - 1]);
}
