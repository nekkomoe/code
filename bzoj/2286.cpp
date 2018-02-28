// 虚树 dp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 500010;

int head[N], rest[N], to[N], w[N], tot, n, m, k;

void add(int u, int v, int len) {
	to[++ tot] = v, w[tot] = len, rest[tot] = head[u], head[u] = tot;
}

typedef long long ll;

int fa[N][30], deep[N], dfn[N];

ll val[N];

void dfs(int u) {
	dfn[u] = ++ *dfn;
	deep[u] = deep[fa[u][0]] + 1;
	for(int i = 1 ; i <= 25 ; ++ i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == fa[u][0]) continue;
		fa[v][0] = u;
		val[v] = min(val[u], (ll) w[i]);
		dfs(v);
	}
}

int rehead[N], rerest[N], reto[N], rew[N], retot;

void readd(int u, int v) {
	if(u != v) reto[++ retot] = v, rerest[retot] = rehead[u], rehead[u] = retot; //, printf("%d -> %d\n", u, v);
}

bool cmp(int a, int b) {
	return dfn[a] < dfn[b];
}

int q[N], s[N], cnt, top;

ll f[N];

int getlca(int u, int v) {
	if(deep[u] < deep[v]) swap(u, v);
	for(int i = 25 ; ~ i ; -- i) if(deep[fa[u][i]] >= deep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 25 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

void redfs(int u) {
	ll ret = 0;
	f[u] = val[u];
	for(int i = rehead[u] ; i ; i = rerest[i]) {
		int v = reto[i];
		// printf("e: %d -> %d\n", u, v);
		redfs(v);
		ret += f[v];
	}
	if(ret) f[u] = min(ret, val[u]);
	// printf("f[%d] = %lld\n", u, f[u]);
	rehead[u] = 0;
}

void sol() {
	retot = 0;
	cnt = top = 0;
	sort(q + 1, q + 1 + k, cmp);
	q[cnt = 1] = q[1];
	for(int i = 2 ; i <= k ; ++ i) if(getlca(q[i], q[cnt]) != q[cnt]) q[++ cnt] = q[i];
	s[++ top] = 1;
	// printf("k = %d cnt = %d\n", k, cnt);
 	for(int i = 1 ; i <= cnt ; ++ i) {
 		int lca = getlca(s[top], q[i]);
 		// printf("lca(%d, %d) = %d\n", s[top], q[i], lca);
 		while(1) {
 	    	if(deep[s[top - 1]] <= deep[lca]) {
 	    		readd(lca, s[top]);
 	    		-- top;
 	    		if(s[top] != lca) s[++ top] = lca;
 	    		break;
 	    	}
 	    	readd(s[top - 1], s[top]);
 	    	-- top;
 		}
 		if(s[top] != q[i]) s[++ top] = q[i];
	}
	-- top;
	while(top) readd(s[top], s[top + 1]), -- top;
	redfs(1);
	printf("%lld\n", f[1]);
}

int main() {
	scanf("%d", &n);
	for(int i = 1, u, v, w ; i < n ; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	val[1] = (1ll << 60), dfs(1);
	scanf("%d", &m);
	for(int i = 1 ; i <= m ; ++ i) {
		scanf("%d", &k);
		for(int j = 1 ; j <= k ; ++ j) {
			scanf("%d", &q[j]);
		}
		sol();
	}
}