#include <bits/stdc++.h>
using namespace std;

const int N = 500000 + 10;

int fa[N], h[N], dis[N], lastans, sz[N];

int get(int x) { if(x == fa[x]) return x; int y = get(fa[x]); h[x] = h[fa[x]] + 1; return y;}

int main() {
	// freopen("data.in", "r", stdin);
	int n, m; scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) fa[i] = i, sz[i] = 1;
	for(int i = 1, op, x, y ; i <= m ; ++ i) {
		scanf("%d%d%d", &op, &x, &y);
		x ^= lastans, y ^= lastans;
		if(op == 0) {
			x = get(x), y = get(y);
			static int tot = 0; ++ tot;
			if(x != y) {
				if(sz[x] < sz[y]) swap(x, y);
				fa[y] = x;
				dis[y] = tot;
				sz[x] += sz[y];
			}
		} else {
			lastans = 0;
			if(get(x) == get(y)) {
				while(x != y) {
					if(h[x] < h[y]) swap(x, y);
					lastans = max(lastans, dis[x]);
					x = fa[x];
				}
			}
			printf("%d\n", lastans);
		}
	}
}