#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N]; 

int main() {
	freopen("absurdity.in", "r", stdin);
	freopen("absurdity.out", "w", stdout); 
	scanf("%*d%s", s + 1);
	int n = strlen(s + 1);
	long long ans = 0, mod = 1e9 + 7;
	for(int i = 1 ; i <= n ; ++ i)
		ans = (ans + 1ll * i * i % mod) % mod;
	printf("%lld\n", ans);
} 
