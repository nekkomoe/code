#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

int fa[N], dis[N], n, q, a[20], T = N - 1, vis[N];

char inp[N];

int get(int x) {
	if(fa[x] == x) return x;
	int f = get(fa[x]);
	dis[x] ^= dis[fa[x]];
	return fa[x] = f;
}

int merge(int x, int y, int v) {
	int fx = get(x), fy = get(y);
	if(fx == fy) return (dis[x] ^ dis[y]) == v;
	if(fx == T) swap(fx, fy);
	fa[fx] = fy;
	dis[fx] = dis[x] ^ dis[y] ^ v;
	return 1;
}

void sol() {
	bool flag = 0;
	for(int i = 0 ; i <= n ; ++ i) fa[i] = i, dis[i] = 0;
	fa[T] = T, dis[T] = 0;
	for(int i = 1, factot = 0 ; i <= q ; ++ i) {
		char op[10]; scanf("%s", op);
		if(op[0] == 'I') {
			++ factot;
			gets(inp);
			int p, q, v;
			if(sscanf(inp, "%d%d%d", &p, &q, &v) == 2) v = q, q = T;
			if(flag) continue;
			if(!merge(p, q, v)) flag = 1, printf("The first %d facts are conflicting.\n", factot);
		} else {
			int k; scanf("%d", &k);
			for(int j = 1 ; j <= k ; ++ j) scanf("%d", &a[j]);

			if(flag) continue;
			int check = 1, ans = 0;
			for(int j = 1 ; j <= k ; ++ j) {
				int x = a[j];
				a[j] = get(x);
				vis[a[j]] ^= 1;
				ans ^= dis[x];
			}
			for(int j = 1 ; j <= k ; ++ j) {
				if(vis[a[j]] && a[j] != T) {
					check = 0;
				}
				vis[a[j]] = 0;
			}
			if(check) printf("%d\n", ans);
			else puts("I don't know.");
		}
	}
}

int main() {
	int T = 0;
	while(scanf("%d%d", &n, &q) && !(!n && !q)) {
		printf("Case %d:\n", ++ T);
		sol();
		puts("");
	}
}
