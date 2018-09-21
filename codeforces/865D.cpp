#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300000 + 10;
int n; priority_queue<int, vector<int>, greater<int> > pq;

int main() {
	scanf("%d", &n);
	ll ans = 0;
	for(int i = 1, p ; i <= n ; ++ i) {
		scanf("%d", &p);
		pq.push(p), pq.push(p);
		ans += p - pq.top();
		pq.pop();
	}
	printf("%lld\n", ans);
}
