#include <bits/stdc++.h>
using namespace std; typedef long long ll; const int N = 40000 + 10;
bitset<N> ans; vector<int> g[N]; int n, m;
void ch(int id, int l, int r, int ql, int qr, int x) {
	int mid = (l + r) >> 1; if(ql <= l && r <= qr) return g[id].push_back(x);
	if(qr <= mid) ch(id << 1, l, mid, ql, qr, x); else if(ql >= mid + 1) ch(id << 1 | 1, mid + 1, r, ql, qr, x);
	else ch(id << 1, l, mid, ql, mid, x), ch(id << 1 | 1, mid + 1, r, mid + 1, qr, x);
}
void dfs(int id, int l, int r, bitset<N> b) {
	int mid = (l + r) >> 1; for(int t: g[id]) b |= b << t; if(l == r) return ans |= b, void();
	dfs(id << 1, l, mid, b), dfs(id << 1 | 1, mid + 1, r, b);
}
int main() {
	ios :: sync_with_stdio(0), cin >> n >> m;
	for(int i = 1, l, r, x ; i <= m ; ++ i) cin >> l >> r >> x, ch(1, 1, n, l, r, x); dfs(1, 1, n, bitset<N> (1));
	int cnt = 0; for(int i = 1 ; i <= n ; ++ i) cnt += ans[i]; cout << cnt << endl;
	for(int i = 1 ; i <= n ; ++ i) if(ans[i]) cout << i << ' ';
}
