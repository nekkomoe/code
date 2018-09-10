#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int sz[N], f[N], n, p, fac[N], invfac[N];

int pw(int a, int b) {
	int r = 1;
	for( ; b ; b >>= 1, a = 1ll * a * a % p)
		if(b & 1)
			r = 1ll * r * a % p;
	return r;
}

int C(int n, int m) {
	if(n < m) return 0;
	if(n < p) return 1ll * fac[n] * invfac[m] % p * invfac[n - m] % p;
	return C(n / p, m / p) * C(n % p, m % p);
}

int main() {
	scanf("%d%d", &n, &p);
	fac[0] = 1; for(int i = 1 ; i <= n ; ++ i) fac[i] = 1ll * fac[i - 1] * i % p;
	invfac[0] = 1; for(int i = 1 ; i <= n ; ++ i) invfac[i] = pw(fac[i], p - 2);
	for(int i = n ; i ; -- i) {
		++ sz[i];
		sz[i / 2] += sz[i];
		if(i * 2 <= n && i * 2 + 1 <= n) {
			f[i] = 1ll * C(sz[i] - 1, sz[i * 2]) * f[i * 2] % p * f[i * 2 + 1] % p;
		} else if(i * 2 <= n) {
			f[i] = f[i * 2];
		} else {
			f[i] = 1;
		}
	}
	printf("%d\n", f[1]);
}
