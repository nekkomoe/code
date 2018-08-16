#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int head[N], rest[N], from[N], to[N], c[N], f[N], tot = 1;

void add_sig(int u, int v, int c, int f) {
	++ tot;
	from[tot] = u, to[tot] = v;
	:: c[tot] = c, :: f[tot] = f;
	rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, int c, int f) {
	add_sig(u, v, c, f);
	add_sig(v, u, -c, 0);
}

int n, m, k;

int S, T, p[51][51][2], cnt;

int val[51][51], inq[N], dis[N], pre[N], ban[51][51];

int spfa() {
	queue<int> q;
	q.push(S);
	for(int i = 1 ; i <= cnt ; ++ i) dis[i] = 0x3f3f3f3f, pre[i] = 0;
	dis[S] = 0;
	inq[S] = 1;
	while(q.size()) {
		int u = q.front(); q.pop(); inq[u] = 0;
//		cout << u << endl;
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i];
			if(f[i] && dis[v] > dis[u] + c[i]) {
				dis[v] = dis[u] + c[i];
				pre[v] = i;
				if(!inq[v]) inq[v] = 1, q.push(v);
			}
		}
	}
	return dis[T] != 0x3f3f3f3f;
}

void sol() {
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			if(!ban[i][j] && (i + j) % 2 == 1)
				ans += val[i][j];
	while(spfa() && m) {
		if(dis[T] > 0) break;
//		cout << dis[T] << ' ' << m << endl;
		int mn = 0x3f3f3f3f;
		for(int i = pre[T] ; i ; i = pre[from[i]]) mn = min(mn, f[i]);
		for(int i = pre[T] ; i ; i = pre[from[i]]) f[i] -= mn, f[i ^ 1] += mn;
		ans += mn * dis[T];
		-- m;
	}
	printf("%d\n", ans);
}

bool check(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n && !ban[x][y];
}

void lk(int x, int y, int i, int j) {
	if(check(x, y)) {
		if(y % 2 == 1) {
			add(p[x][y][0], p[i][j][0], 0, 1);
		} else {
			add(p[i][j][1], p[x][y][0], 0, 1);
		}
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	S = ++ cnt, T = ++ cnt;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) {
			scanf("%d", &val[i][j]);
			p[i][j][0] = ++ cnt;
			p[i][j][1] = ++ cnt;
		}
	}
	for(int i = 1, x, y ; i <= k ; ++ i) {
		scanf("%d%d", &x, &y);
		ban[x][y] = 1;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) {
			if(ban[i][j]) continue;
			if((i + j) % 2 == 1) {
				// 奇数 
				add(p[i][j][0], p[i][j][1], -val[i][j], 1);
				
				lk(i - 1, j, i, j);
				lk(i, j + 1, i, j);
				lk(i + 1, j, i, j);
				lk(i, j - 1, i, j);
				
			} else {
				// 偶数 
				if(j % 2 == 1) {
					// 奇数行
					add(S, p[i][j][0], 0, 1);
				} else {
					// 偶数行 
					add(p[i][j][0], T, 0, 1);
				}
			}
		}
	}
	sol();
}
