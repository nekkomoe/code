#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
const int N = 7e5 + 10;

int n, m, sz[N], lc[N], rc[N], root[N], val[N];

void up(int x) { sz[x] = sz[lc[x]] + sz[rc[x]] + 1; }

pair<int, int> split(int x, int k) {
	pair<int, int> res;
	if(x) {
		if(sz[lc[x]] >= k) {
			res = split(lc[x], k);
			lc[x] = res.second;
			res.second = x;
		} else {
			res = split(rc[x], k - sz[lc[x]] - 1);
			rc[x] = res.first;
			res.first = x;
		}
		up(x);
	}
	return res;
}

int merge(int x, int y) {
	if(!x || !y) return x | y;
	if(rand() % (sz[x] + sz[y]) < sz[x]) {
		rc[x] = merge(rc[x], y);
		up(x);
		return x;
	} else {
		lc[y] = merge(x, lc[y]);
		up(y);
		return y;
	}
}

queue<int> rs;
int nd(int val) {
	static int tot = 0;
	if(rs.size()) {
		int u = rs.front(); rs.pop();
		if(lc[u]) rs.push(lc[u]);
		if(rc[u]) rs.push(rc[u]);
		lc[u] = rc[u] = 0, sz[u] = 1, :: val[u] = val;
		return u;
	} else {
		++ tot;
		:: val[tot] = val;
		sz[tot] = 1;
		return tot;
	}
}

int le(int x, int v) {
	if(!x) return 0;
	if(v >= val[x]) return sz[lc[x]] + 1 + le(rc[x], v);
	return le(lc[x], v);
}

void ins(int &x, int v) {
	pair<int, int> res = split(x, le(x, v));
	x = merge(res.first, merge(nd(v), res.second));
}

void dfs(int u) {
	if(u) dfs(lc[u]), printf("%d ", val[u]), dfs(rc[u]);
}

void del(int &x, int v) {
	pair<int, int> res = split(x, le(x, v - 1));
	pair<int, int> ser = split(res.second, 1);
	if(ser.first) rs.push(ser.first);
	x = merge(res.first, ser.second);
}

cc_hash_table<int, int> tr;
int tot, a[N];

inline int read() {
	int x = 0, c = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
	return x;
}

int main() {
	n = read(), m = read();
	for(int i = 1, x ; i <= n ; ++ i) {
		x = a[i] = read();
		if(tr.find(x) == tr.end()) tr[x] = ++ tot;
		ins(root[tr[x]], i);
	}
	for(int i = 1, lastans = 0 ; i <= m ; ++ i) {
		if(read() == 1) {
			int l = ((ll) read() + lastans) % n + 1;
			int	r = ((ll) read() + lastans) % n + 1;
			int	k = read();
			if(l > r) swap(l, r);
			if(tr.find(k) == tr.end()) lastans = 0;
			else lastans = le(root[tr[k]], r) - le(root[tr[k]], l - 1);
			printf("%d\n", lastans);
		} else {
			int p = ((ll) read() + lastans) % n + 1;
			int	x = read();
			if(tr.find(x) == tr.end()) tr[x] = ++ tot;
			del(root[tr[a[p]]], p);
			ins(root[tr[x]], p);
			a[p] = x;
		}
	}
}
