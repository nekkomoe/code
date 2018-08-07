#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, p = 1e9 + 7;
int fac[N], inv[N], n, m;
int pw(int a, int b) {
	int r = 1;
	for( ; b ; b >>= 1, a = 1ll * a * a % p) if(b & 1) r = 1ll * r * a % p;
	return r;
}
int C(int n, int m) {
	return 1ll * fac[n] * inv[m] % p * inv[n - m] % p;
}
int main() {
	scanf("%d%d", &n, &m);
	inv[0] = fac[0] = 1;
	for(int i = 1 ; i <= N - 10 ; ++ i) fac[i] = 1ll * fac[i - 1] * i % p, inv[i] = pw(fac[i], p - 2);
	int ans = 0, sig = 1;
	for(int k = 0 ; k <= m ; ++ k) {
		ans = (1ll * ans + 1ll * sig * C(m, k) * pw(m - k, n) % p) % p;
		sig = - sig;
	}
	printf("%d\n", (1ll * ans % p + p) % p);
}
