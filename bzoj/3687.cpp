#include <bits/stdc++.h>
using namespace std; typedef long long ll;
bitset<2000000 + 10> f; int n;
int main() {
	scanf("%d", &n); f[0] = 1;
	for(int i = 1, x ; i <= n ; ++ i) scanf("%d", &x), f ^= f << x;
	int ans = 0; for(int i = 0 ; i <= 2000000 ; ++ i) if(f[i]) ans ^= i; printf("%d\n", ans);
}
