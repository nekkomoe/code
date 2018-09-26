#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10;
char s[N]; int n, m;
struct LN { int l, r, id; } ln[N];
bool cmp(LN a, LN b) { return a.l == b.l ? a.r > b.r : a.l < b.l; }
bool operator < (LN a, LN b) { return a.r > b.r; }
priority_queue<LN> pq;
bitset<N> cur, out; ll ans;

int main() {
	freopen("failure.in", "r", stdin);
	freopen("failure.out", "w", stdout); 
	scanf("%*d%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &ln[i].l, &ln[i].r), ln[i].id = i;
	sort(ln + 1, ln + 1 + n, cmp);
	for(int i = 1 ; i <= m ; ++ i) pq.push(ln[i]), cur[ln[i].id] = 1;
	out = cur, ans = max(pq.top().r - ln[m].l, 0);
	for(int i = m + 1 ; i <= n ; ++ i) {
		pq.push(ln[i]), cur[ln[i].id] = 1;
		cur[pq.top().id] = 0, pq.pop();
		ll tmp = max(pq.top().r - ln[i].l, 0);
		if(tmp > ans) {
			ans = tmp;
			out = cur;
		}
	}
	printf("%lld\n", ans);
	for(int i = 1 ; i <= n ; ++ i)
		if(out[i])
			printf("%d ", i);
	puts("");
}
