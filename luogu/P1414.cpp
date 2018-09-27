#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10000 + 10, INF = 1e6 + 10;
int cnt[INF], f[N], n;

int main() {
	scanf("%d", &n);
	for(int i = 1, x ; i <= n ; ++ i) {
		scanf("%d", &x);
		++ cnt[x];
	}
	for(int i = 1 ; i < INF ; ++ i)
		for(int j = i + i ; j < INF ; j += i)
			cnt[i] += cnt[j];
	for(int i = 1 ; i < INF ; ++ i)	
		f[cnt[i]] = max(f[cnt[i]], i);
	for(int i = n ; i ; -- i)
		f[i] = max(f[i], f[i + 1]);
	for(int i = 1 ; i <= n ; ++ i)
		printf("%d\n", f[i]);
}
