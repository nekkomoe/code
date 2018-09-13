#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int a[N], head[N], rest[N], to[N], tot, deg[N], n;
void add(int u, int v) {
	++ deg[u];
	to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

double s[N];

void dfs(int u, int fa, double p) {
	s[u] = p + log(a[u]);
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u, p + log(deg[u]));
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	for(int i = 1, u, v ; i < n ; ++ i) scanf("%d%d", &u, &v), add(u, v);//, add(v, u);
	dfs(1, 0, log(1));
	sort(s + 1, s + 1 + n);
	int ans = 1, tot = 1;
	for(int i = 2 ; i <= n ; ++ i)
		if(fabs(s[i] - s[i - 1]) < 1e-8)
			ans = max(ans, ++ tot);
		else
			tot = 1;
	printf("%d\n", n - ans);
}
