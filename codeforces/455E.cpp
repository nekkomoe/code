%:pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
#define int ll
int n, q, a[N], s[N];
struct P { int x, y; } tmp[N];
inline P operator - (P a, P b) { return (P) { a.x - b.x, a.y - b.y }; }
inline int operator * (P a, P b) { return a.x * b.y - b.x * a.y; }
inline bool operator < (P a, P b) { return a.x == b.x ? a.y > b.y : a.x < b.x; }
inline bool check(P a, P b, P c) { return (b - a) * (c - a) <= 0; }
inline int calcbyp(int x, int y, P p) { return p.y + s[y] + (x - y) * p.x; }
vector<P> tb[N * 10];
#define lc (id << 1)
#define rc (id << 1 | 1)
template<typename T> inline void read(T &x) {
	x = 0;
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}
void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) tb[id].push_back((P) { a[l], -s[l] + l * a[l] });
	else {
		build(lc, l, mid), build(rc, mid + 1, r);
		int tp = 0;
		for(auto p : tb[lc]) tmp[tp ++] = p;
		for(auto p : tb[rc]) tmp[tp ++] = p;
		if(tb[lc].size() && tb[rc].size()) inplace_merge(tmp, tmp + tb[lc].size(), tmp + tp);
		for(int i = 0 ; i < tp ; ++ i) {
			while(tb[id].size() >= 2 && check(*(tb[id].end() - 2), tb[id].back(), tmp[i])) tb[id].pop_back();
			tb[id].push_back(tmp[i]);
		}
	}
}
int query(int id, int l, int r, int x, int y) {
	int mid = (l + r) >> 1, ql = y - x + 1, qr = y, res = 0x3f3f3f3f;
	if(ql > r || qr < l) return res;
	else if(ql <= l && r <= qr) {
		if(tb[id].size() >= 2) {
			int l = 0, r = tb[id].size() - 1;
			while(r - l >= 3) {
				int m1 = (l + l + r) / 3, m2 = (r + l + r) / 3;
				int t1 = calcbyp(x, y, tb[id][m1]), t2 = calcbyp(x, y, tb[id][m2]);
				if(t1 <= t2) r = m2;
				else l = m1;
			}
			for(int i = l ; i <= r ; ++ i) res = min(res, calcbyp(x, y, tb[id][i]));
		} else for(auto p : tb[id]) res = min(res, calcbyp(x, y, p));
		return res;
	} else return min(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
signed main() {
	read(n);
	for(int i = 1 ; i <= n ; ++ i) read(a[i]), s[i] = s[i - 1] + a[i];
	build(1, 1, n);
	read(q);
	for(int i = 1, x, y ; i <= q ; ++ i) {
		read(x), read(y);
		printf("%I64d\n", query(1, 1, n, x, y));
	}
}
