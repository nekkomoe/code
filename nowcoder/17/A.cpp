#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10;
int n;
priority_queue<int> pq;

int main() {
	scanf("%d", &n);
	for(int i = 1, x ; i <= n ; ++ i) scanf("%d", &x), pq.push(x);
	ll ans = 0;
	while(pq.size() > 1) {
		int u = pq.top(); pq.pop();
		int v = pq.top(); pq.pop();
		ans += u + v;
		pq.push(u + v);
	}
	printf("%lld\n", ans);
}
