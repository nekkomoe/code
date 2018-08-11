#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;

struct REL { int a, b; } rel[N];

int n, m;

int head[N], rest[N * 2], to[N * 2], tot;

void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }

int fa[N][21], dep[N];

void dfs(int u, int f) {
	fa[u][0] = f, dep[u] = dep[f] + 1;
	for(int i = head[u] ; i ;  i = rest[i]) {
		int v = to[i];
		if(v == f) continue;
		dfs(v, u);
	}
}

int getlca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int dis[N], acc[N];

int get(int x) {
	if(x == acc[x]) return x;
	int y = acc[x];
	acc[x] = get(acc[x]);
	dis[x] ^= dis[y];
	return acc[x];
}

void merge(int a, int d) {
	a = get(a);
	while(dep[a] >= dep[d] + 2) {
		acc[a] = get(fa[a][0]);
		a = get(a);
	}
}

const int p = 1e9 + 7;
typedef long long ll;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
	return r;
}

int main() {
	freopen("usmjeri.in", "r", stdin);
	freopen("usmjeri.out", "w", stdout);
	cin >> n >> m;
	for(int i = 1, u, v ; i < n ; ++ i) {
		cin >> u >> v;
		add(u, v), add(v, u);
	}
	for(int i = 1 ; i <= n ; ++ i) acc[i] = i;
	dfs(1, 0);
	for(int j = 1 ; j <= 20 ; ++ j)
		for(int i = 1 ; i <= n ; ++ i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	for(int i = 1 ; i <= m ; ++ i) {
		cin >> rel[i].a >> rel[i].b;
		int a = rel[i].a, b = rel[i].b, d = getlca(a, b);
		merge(a, d);
		merge(b, d);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int a = rel[i].a, b = rel[i].b, fa = get(a), fb = get(b), d = getlca(a, b);
		if(d == a || d == b) continue;
		if(fa == fb) {
			if((dis[a] ^ dis[b]) == 0) {
				puts("0");
				return 0;
			}
		} else {
			dis[fa] = dis[a] ^ dis[b] ^ 1;
			acc[fa] = get(b);
			
		}
	}
	int ans = 0;
	for(int i = 2 ; i <= n ; ++ i) {
		ans += get(i) == i;
	}
	cout << pw(2, ans) << endl;
}
