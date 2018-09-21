#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10000 + 10;
int n, m, w[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &w[i]), w[i] *= 2;
	for(int i = 1, u, v, x ; i <= m ; ++ i) scanf("%d%d%d", &u, &v, &x), w[u] += x, w[v] += x;
	ll s1 = 0, s2 = 0;
	sort(w + 1, w + 1 + n);
	while(n) s1 += w[n --], s2 += w[n --];
	printf("%lld\n", (s1 - s2) / 2);
}
