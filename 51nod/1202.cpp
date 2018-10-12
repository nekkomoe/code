#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int pos[N], n, f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1, x ; i <= n ; ++ i) {
		scanf("%d", &x);
		if(!pos[x]) f[i] = (2ll * f[i - 1] + 1) % mod;
		else f[i] = (2ll * f[i - 1] - f[pos[x] - 1]) % mod;
		pos[x] = i;
	}
	printf("%lld\n", (f[n] % mod + mod) % mod);
}
