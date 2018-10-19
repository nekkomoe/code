#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 4010;

int n, a[N], b[N], c[N], d[N], t[N * N], top;

int get(int x) {
	return upper_bound(t + 1, t + 1 + top, x) - lower_bound(t + 1, t + 1 + top, x);
}

int main() {
//	freopen("data.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i)
		scanf("%d", &a[i]),
//	for(int i = 1 ; i <= n ; ++ i)
		scanf("%d", &b[i]),
//	for(int i = 1 ; i <= n ; ++ i)
		scanf("%d", &c[i]),
//	for(int i = 1 ; i <= n ; ++ i)
		scanf("%d", &d[i]);
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			t[++ top] = a[i] + b[j];
	sort(t + 1, t + 1 + top);
	
	long long ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			ans += get(- c[i] - d[j]);
	
	printf("%lld\n", ans);
}
