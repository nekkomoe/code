#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const double eps = 1e-8, inf = 1e15;
int n, a, b;

int head[N], rest[N], from[N], to[N], f[N], tot = 1;
double c[N];
void add_sig(int u, int v, double c, int f) {
	from[++ tot] = u, to[tot] = v, :: c[tot] = c, :: f[tot] = f, rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, double c, int f) {
	add_sig(u, v, c, f);
	add_sig(v, u, -c, 0);
}

int Sa, Sb, T, S, pre[N], inq[N];

double dis[N], ans, p[N], q[N];

int spfa() {
	queue<int> q;
	for(int i = 1 ; i <= S ; ++ i) dis[i] = -inf, pre[i] = 0;
	q.push(S);
	dis[S] = 0, inq[S] = 1;
	while(q.size()) {
		int u = q.front(); q.pop(); inq[u] = 0;
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i];
			if(f[i] && dis[u] + c[i] > dis[v] + 1e-8) {
				dis[v] = dis[u] + c[i];
				pre[v] = i;
				if(!inq[v]) inq[v] = 1, q.push(v);
			}
		}
	}
	return dis[T] > -inf;
}

int main() {
	scanf("%d%d%d", &n, &a, &b);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lf", &p[i]);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lf", &q[i]);
	Sa = n + 1, Sb = n + 2, T = n + 3, S = n + 4;
	add(S, Sa, 0, a);
	add(S, Sb, 0, b);
	for(int i = 1 ; i <= n ; ++ i) {
		add(Sa, i, p[i], 1);
		add(Sb, i, q[i], 1);
		add(i, T, 0, 1);
		add(i, T, -p[i] * q[i], 1);
	}
	while(spfa()) {
		int mn = 0x3f3f3f3f;
		for(int i = pre[T] ; i ; i = pre[from[i]]) mn = min(mn, f[i]);
		for(int i = pre[T] ; i ; i = pre[from[i]]) f[i] -= mn, f[i ^ 1] += mn;
		ans += mn * dis[T];
	}
	printf("%lf\n", ans);
}
