#include <bits/stdc++.h>
using namespace std;
const int N = 2010, p = 1e9 + 7;
int h, w, n, f[N], fac[200010], inv[200010];
int pw(int a, int b) {
	int r = 1;
	for( ; b ; b >>= 1, a = 1ll * a * a % p) if(b & 1) r = 1ll * r * a % p;
	return r;
}
int C(int n, int m) {
	return 1ll * fac[n + m] * inv[n] % p * inv[m] % p;
}
struct P {
	int x, y;
} pt[N];
bool operator < (P a, P b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
int main() {
	scanf("%d%d%d", &h, &w, &n);
	for(int i = fac[0] = 1 ; i <= h + w ; ++ i) fac[i] = 1ll * fac[i - 1] * i % p, inv[i] = pw(fac[i], p - 2);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &pt[i].x, &pt[i].y);
	pt[++ n] = (P) { h, w };
	sort(pt + 1, pt + 1 + n);
	inv[0] = f[0] = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		f[i] = C(pt[i].x - 1, pt[i].y - 1);
		for(int j = 1 ; j < i ; ++ j) {
			if(pt[j].x <= pt[i].x && pt[j].y <= pt[i].y) {
				f[i] = (1ll * f[i] - 1ll * f[j] * C(pt[i].x - pt[j].x, pt[i].y - pt[j].y) % p) % p;
			}
		}
	}
	printf("%d\n", (1ll * f[n] % p + p) % p);
}
