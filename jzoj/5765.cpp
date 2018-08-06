#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5000000 + 10, mod = 1e9 + 7;
int n, k, m, has1[N], f[10][2][2], g[10], a[10];
char s[N];
ll ans, fac[N];
int pw(int a, int b) {
	int r = 1;
	for( ; b ; b >>= 1, a = (ll) a * a % mod) if(b & 1) r = (ll) r * a % mod;
	return r;
}

void dfs(int x, int y) {
	if(x == n + 1) {
		int j = 0, k = 0, t = 1, r = 0;
		for(int i = 1 ; i <= y ; ++ i) {
			if(a[i] & 1) ++ j; else ++ k;
			t = (ll) t * fac[a[i] - 1] % mod;
			r += a[i] - 1;
		}
		t = (ll) t * g[j] % mod * pw(g[2], k) % mod;
		ans += t * (r & 1 ? -1 : 1);
	} else {
		for(int i = 1 ; i <= y + 1 ; ++ i) {
			++ a[i];
			dfs(x + 1, max(y, i));
			-- a[i];
		}
	}
}

int main() {
    freopen("mothergoose.in", "r", stdin);
    freopen("mothergoose.out", "w", stdout);
    scanf("%d%d%s", &n, &k, s + 1), m = strlen(s + 1);
    for(int i = g[0] = fac[0] = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    for(int i = 1 ; i <= m ; ++ i)
    	for(int j = 1 ; j < k ; ++ j)
    		s[i + j * m] = s[i]; m *= k;
    for(int i = 1 ; i <= m ; ++ i)
    	has1[i] = has1[i - 1] | (s[i] == '1');
    int t = 0, r = 1;
    for(int i = m ; i ; -- i) {
    	if(s[i] == '1') {
    		for(int j = 0 ; j <= n ; ++ j)
    			for(int k = 0 ; k <= 1 ; ++ k)
    				for(int l = 0 ; l <= 1 ; ++ l)
    					f[j][k][l] = 0;
    		f[0][0][0] = 1;
    		for(int j = 0 ; j < n ; ++ j) {
    			for(int k = 0 ; k <= 1 ; ++ k) {
    				(f[j + 1][k ^ 1][0] += (ll) f[j][k][0] * t % mod) %= mod;
    				(f[j + 1][k][1] += f[j][k][0]) %= mod;
    				(f[j + 1][k ^ 1][1] += (ll) f[j][k][1] * t % mod) %= mod;
    				(f[j + 1][k][1] += (ll) f[j][k][1] * r % mod) %= mod;
    			}
    		}
    		for(int j = 0 ; j <= n ; ++ j)
    			if((j & 1) == 0 || !has1[i - 1])
    				g[j] = ((ll) g[j] + f[j][0][1]) % mod;
    		t = ((ll) t + r) % mod;
    	}
    	r = ((ll) r << 1) % mod;
    }
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i) ans = (ans * pw(i, mod - 2)) % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
}
