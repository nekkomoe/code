#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 110;
int n, m, d[N], c[N][20];
ll f[2][1 << 17];
int w(int x) { return 1 << (x - 1); }
void setmn(ll &x, ll y) { x = min(x, y); }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &d[i]);
		for(int j = 1 ; j <= m ; ++ j) {
			scanf("%d", &c[i][j]);
		}
	}
	memset(f, 0x3f, sizeof f);
	int p = 0;
	f[p][0] = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		p ^= 1;
		for(int s = 0 ; s < (1 << m) ; ++ s) {
			f[p][s] = f[p ^ 1][s] + d[i];
		}
		for(int j = 1 ; j <= m ; ++ j) {
			for(int s = 0 ; s < (1 << m) ; ++ s) {
				if(s & w(j)) continue;
				setmn(f[p][s + w(j)], f[p][s] + c[i][j]);
			}
		}
		for(int s = 0 ; s < (1 << m) ; ++ s) {
			setmn(f[p][s], f[p ^ 1][s]);
		}
	}
	printf("%lld\n", f[p][(1 << m) - 1]);
}
