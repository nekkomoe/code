#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500000 + 10;
struct T { int id; ll val; };
bool operator < (T a, T b) { return a.val < b.val; }
priority_queue<T> pq;
ll a[N]; int l[N], r[N], vis[N];

int main() {
	int n, k; cin >> n >> k;
	if(2 * k > n)  return puts("Error!"), 0;
	for(int i = 1 ; i <= n ; ++ i) cin >> a[i], pq.push((T) { i, a[i] }), l[i] = i - 1, r[i] = i + 1;
	ll ans = 0;
	l[1] = n, r[n] = 1;
	for(int i = 1 ; i <= k ; ++ i) {
		while(pq.size() && vis[pq.top().id]) pq.pop();
		T t = pq.top(); pq.pop();
//		if(t.val < 0) break;
		ans += t.val;
		int id = t.id;
		t.val = a[id] = -a[id] + a[l[id]] + a[r[id]];
		vis[l[id]] = vis[r[id]] = 1;
		l[id] = l[l[id]], r[id] = r[r[id]];
		l[r[id]] = id, r[l[id]] = id;
		pq.push(t);
	}
	printf("%lld\n", ans);
}
