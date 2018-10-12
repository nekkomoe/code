#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, m, k, T, a[N];
struct Q {
	int l, r, id;
} q[N]; int ans[N];
bool operator < (Q a, Q b) {
	return a.r < b.r;
}
vector<int> pos[N];
int bit[N];
void sig(int x, int y) {
	for( ; x <= n ; x += x & -x)
		bit[x] += y;
}
void add(int l, int r, int x) {
	sig(l, x), sig(r + 1, -x);
}
int ask(int x) {
	int r = 0;
	for( ; x ; x -= x & -x)
		r += bit[x];
	return r;
}

int main() {
//	freopen("data.in", "r", stdin);
	scanf("%d%d%d%d", &n, &m, &k, &T);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	for(int i = 1 ; i <= m ; ++ i) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + 1 + m);
	for(int i = 1 ; i <= k ; ++ i) pos[i].push_back(0); 
	for(int i = 1, j = 0 ; i <= n ; ++ i) {
		int sz = pos[a[i]].size(); pos[a[i]].push_back(i);
		if(sz >= T) add(pos[a[i]][sz - T] + 1, pos[a[i]][sz - T + 1], 1);
		if(sz > T) add(pos[a[i]][sz - T - 1] + 1, pos[a[i]][sz - T], -1);
		while(j + 1 <= m && q[j + 1].r == i) {
			++ j;
			ans[q[j].id] = ask(q[j].l);
		}
	}
	for(int i = 1 ; i <= m ; ++ i) printf("%d\n", ans[i]);
}
