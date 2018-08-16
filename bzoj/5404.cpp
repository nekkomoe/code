#include <bits/stdc++.h>
using namespace std;

int n, m, q;

const int N = 3e5 + 10;

int head[N], rest[N * 2], to[N * 2], tot, a[N], que[N], rev[N];

void add(int u, int v) {
	to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int sz[N], top[N], son[N], dep[N], fa[N], cnt, dfn[N], dfn_clk, pos[N];

void dfs(int u) {
	dfn[u] = ++ dfn_clk;
	sz[u] = 1, son[u] = 0, dep[u] = dep[fa[u]] + 1;
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		fa[v] = u;
		dfs(v);
		sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}

void dfs(int u, int tp) {
	top[u] = tp;
	pos[u] = ++ cnt;
	rev[cnt] = u;
	if(son[u]) dfs(son[u], tp);
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		if(v == son[u]) continue;
		dfs(v, v);
	}
}

bool cmp(int a, int b) { return dfn[a] < dfn[b]; }

int getlca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

bitset<1001> bs[N * 4], ck[6], mt;

#define lc (id << 1)
#define rc (id << 1 | 1)

void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) {
		bs[id].set(a[rev[l]]);
	} else {
		build(lc, l, mid), build(rc, mid + 1, r);
		bs[id] = bs[lc] | bs[rc];
	}
}

void query(int id, int l, int r, int ql, int qr, int rt) {
//	cout << l << ' ' << r << ' ' << ql << ' ' << qr << endl; getchar();
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) ck[rt] |= bs[id];
	else if(ql >= mid + 1) query(rc, mid + 1, r, ql, qr, rt);
	else if(qr <= mid) query(lc, l, mid, ql, qr, rt);
	else query(lc, l, mid, ql, mid, rt), query(rc, mid + 1, r, mid + 1, qr, rt);
}

void getbs(int id, int u, int lca) {
	ck[id] = 0;
	while(top[u] != top[lca]) {
//		cout << "u = " << u << endl;
		query(1, 1, n, pos[top[u]], pos[u], id);
		u = fa[top[u]];
	}
//	cout << pos[lca] << ' ' << pos[u] << endl;
	query(1, 1, n, pos[lca], pos[u], id);
}
int fafa[N];
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 2, p ; i <= n ; ++ i) {
		scanf("%d", &p);
		add(p, i);
	}
	for(int i = 0 ; i < (1 << 5) ; ++ i) fafa[i] = fafa[i >> 1] + (i & 1);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	
	dfs(1), dfs(1, 1), build(1, 1, n);
	
//	cout << "cnt = " << cnt << endl;
	
	for(int i = 1, c ; i <= q ; ++ i) {
		scanf("%d", &c);
		for(int j = 1 ; j <= c ; ++ j) {
			scanf("%d", &que[j]);
		}
		
		
		sort(que + 1, que + 1 + c, cmp);
		
//		for(int j = 1 ; j <= c ; ++ j) cout << que[j] << ' '; cout << endl;
		
//		cout << "getlca: " << que[1] << ' ' << que[c] << endl;
		
		int lca = getlca(que[1], que[c]);
		
//		cout << "lca = " << lca << endl;
		
		for(int j = 1 ; j <= c ; ++ j) {
			getbs(j, que[j], lca);
//			cout << ck[j] << endl;
		}
//		puts("!");
		
		int ans = 0x3f3f3f3f;
		for(int s = 1 ; s < (1 << c) ; ++ s) {
			mt = 0;
			for(int j = 1 ; j <= c ; ++ j) if((s >> (j - 1)) & 1) mt |= ck[j];
//			cout << "s = " << bitset<5> (s) << "count = " << mt.count() << " fafa = " << fafa[s] << endl;
			ans = min(ans, int(mt.count() / fafa[s]));
		}
		printf("%d\n", ans * c);
	}
}
