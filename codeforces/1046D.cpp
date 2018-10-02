#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
double a[N];
int n, q;
void add(int x, double y) {
	// a[x] += y; return ;


	for( ; x <= n ; x += x & -x)
		a[x] += y;
}

double sig(int x) {
	if(x == 0) return 0;
	double r = 0;
	for( ; x ; x -= x & -x)
		r += a[x];
	return r;
}

double ask(int l, int r) {
	// double res = 0;
	// for(int i = l ; i <= r ; ++ i)
	// 	res += a[i];
	// return res;

	if(l > r) return 0;
	return sig(r) - sig(l - 1);
}

vector<int> g[N];

int l[N], r[N], tot, pos[N], fa[N];

void bfs() {
	queue<int> q;
	q.push(1); pos[1] = ++ tot;
	while(q.size()) {
		int u = q.front(); q.pop();
		l[u] = tot + 1;
		for(int v: g[u])
			if(v != fa[u])
				fa[v] = u,
				pos[v] = ++ tot,
				r[u] = tot,
				q.push(v);
	}
}

double val[N];

double query(int u, double d) {
	double res = 0;
	if(fa[u]) res += d * ask(pos[fa[u]], pos[fa[u]]);
	res += d * ask(l[u], r[u]);
	return res;
}
int main() {
	// freopen("data.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i)
		scanf("%lf", &val[i]);
	for(int i = 1, u, v ; i < n ; ++ i)
		scanf("%d%d", &u, &v),
		++ u, ++ v,
		g[u].push_back(v),
		g[v].push_back(u);
	bfs();

	// for(int i = 1 ; i <= n ; ++ i)
	// 	printf("%d: pos = %d, [%d, %d]\n", i, pos[i], l[i], r[i]);

	double ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		val[i] = 1 - val[i];
		double delta = val[i] - ask(pos[i], pos[i]);
		ans += delta;
		ans -= query(i, delta);
		add(pos[i], delta);
	}
	scanf("%d", &q);
	for(int i = 1 ; i <= q ; ++ i) {
		int u; double val;
		scanf("%d%lf", &u, &val), ++ u;
		val = 1 - val;
		double delta = val - ask(pos[u], pos[u]);
		ans += delta;
		ans -= query(u, delta);
		add(pos[u], delta);
		printf("%.5lf\n", ans);
	}
}
