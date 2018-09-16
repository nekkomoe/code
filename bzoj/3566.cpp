#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500000 + 10;
int n;
int head[N], rest[N * 2], to[N * 2], tot;
double p[N * 2], q[N], f[N], g[N];

void add(int u, int v, double p) {
	to[++ tot] = v, :: p[tot] = p, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u, int fa) {
	f[u] = 1 - q[u];
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		f[u] *= f[v] + (1 - f[v]) * (1 - p[i]);
	}
}

void get(int u, int fa) {
	if(!fa) g[u] = 1;
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == fa) continue;
		double t = g[u] * f[u] / (f[v] + (1 - f[v]) * (1 - p[i]));
		g[v] = t + (1 - t) * (1 - p[i]);
		get(v, u);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i < n ; ++ i) {
		int u, v; double p;
		scanf("%d%d%lf", &u, &v, &p), p /= 100;
		add(u, v, p), add(v, u, p);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%lf", &q[i]), q[i] /= 100;
	}
	dfs(1, 0), get(1, 0);
	double ans = 0;
	for(int i = 1 ; i <= n ; ++ i) ans += 1 - f[i] * g[i];
	printf("%.6lf\n", ans);
}
