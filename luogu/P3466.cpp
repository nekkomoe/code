#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000000 + 10;
int n, k, a[int(1e5) + 10], val[N], sz[N], lc[N], rc[N], root;
ll sum[N], tot, ans = -1;
int nd(int x) { static int tot = 0; return val[++ tot] = x, sum[tot] = val[tot], sz[tot] = 1, tot; }
void up(int x) { sz[x] = sz[lc[x]] + sz[rc[x]] + 1, sum[x] = sum[lc[x]] + sum[rc[x]] + val[x]; }
int merge(int x, int y) {
	if(!x || !y) return x | y;
	if(rand() % (sz[x] + sz[y]) < sz[x]) return rc[x] = merge(rc[x], y), up(x), x;
	else return lc[y] = merge(x, lc[y]), up(y), y;
}
pair<int, int> split(int x, int k) {
	pair<int, int> res;
	if(x) {
		if(sz[lc[x]] >= k) res = split(lc[x], k), lc[x] = res.second, res.second = x;
		else res = split(rc[x], k - sz[lc[x]] - 1), rc[x] = res.first, res.first = x;
		up(x);
	}
	return res;
}
int le(int x, int v) {
	if(!x) return 0;
	if(v < val[x]) return le(lc[x], v);
	else return sz[lc[x]] + 1 + le(rc[x], v);
}
void ins(int x) {
	pair<int, int> p = split(root, le(root, x));
	root = merge(p.first, merge(nd(x), p.second));
}
void del(int x) {
	pair<int, int> p = split(root, le(root, x) - 1);
	pair<int, int> q = split(p.second, 1);
	root = merge(p.first, q.second);
}
int ttt, md, pos;
ll calc() {
	pair<int, int> p = split(root, k / 2);
	pair<int, int> q = split(p.second, 1);
	int mid = val[q.first]; ttt = mid;
	ll res = 0;
	res += 1ll * sz[p.first] * mid - sum[p.first];
	res += sum[q.second] - 1ll * sz[q.second] * mid;
	root = merge(p.first, merge(q.first, q.second));
	return res;
}

void dfs(int u) {
	if(u) dfs(lc[u]), printf("%d ", val[u]), dfs(rc[u]);
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1, x ; i <= n ; ++ i) {
		scanf("%d", &x), a[i] = x, tot += x;
		ins(x);
		if(i - k + 1 >= 1) {
			if(ans == -1) ans = tot;
			int t = i - k;
			if(t >= 1) {
				del(a[t]);
				tot -= a[t];
			}
			ll tmp = calc();
			if(tmp < ans) {
				ans = tmp;
				pos = i - k + 1;
				md = ttt;
			}
		}
	}
	printf("%lld\n", ans);
	for(int i = 1 ; i <= n ; ++ i) {
		if(pos <= i && i <= pos + k - 1) {
			printf("%d\n", md);
		} else {
			printf("%d\n", a[i]);
		}
	}
}
