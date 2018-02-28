// 拓扑排序判环+更新

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 300010;

int head[N], rest[N], to[N], tot;

int n, m, deg[N], cnt, f[N][30], ans;

char val[N];

int main() {
	scanf("%d%d", &n, &m);
	scanf("%s", val + 1);
	for(int i = 1, u, v ; i <= m ; ++ i) {
		scanf("%d%d", &u, &v);
		to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
		++ deg[v];
	}
	queue<int> q;
	for(int i = 1 ; i <= n ; ++ i) {
		if(!deg[i]) {
			q.push(i);
			ans = max(ans, ++ f[i][val[i] - 'a']);
		}
	}
	while(q.size()) {
		int u = q.front();
		q.pop();
		++ cnt;
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i];
			if(!-- deg[v]) {
				q.push(v);
			}
			for(int j = 0 ; j < 26 ; ++ j) ans = max(ans, f[v][j] = max(f[v][j], f[u][j] + (val[v] - 'a' == j)));
		}
	}
	if(cnt < n) puts("-1");
	else printf("%d\n", ans);
}