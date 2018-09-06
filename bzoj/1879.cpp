#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e6 + 3;
char s[20][55];
int n, k, vis[55], len;
ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
	return r;
}
ll calc(int s) {
	for(int i = 1 ; i <= len ; ++ i) {
		vis[i] = 0;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if((s >> (i - 1)) & 1) {
			for(int j = 1 ; j <= len ; ++ j) {
				char c = :: s[i][j];
				if(c == '?') continue;
				if(vis[j] && vis[j] != c) {
					return 0;
				}
				vis[j] = c;
			}
		}
	}
	
	ll res = 1;
	for(int i = 1 ; i <= len ; ++ i) {
		if(vis[i]) continue;
		res = res * 26 % mod;
	}
	
	return res;
}

int C[20][20];

void sol() {
	scanf("%d%d", &n, &k);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%s", s[i] + 1);
	}
	len = strlen(s[1] + 1);
	int ans = 0;
	for(int s = 0 ; s < (1 << n) ; ++ s) {
		int cnt = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			if((s >> (i - 1)) & 1) {
				++ cnt;
			}
		}
		if(cnt >= k) {
			ll sig = ((cnt - k) & 1) ? -1 : 1;
			ans = (ans + sig * C[cnt][k] * calc(s)) % mod;
		}
	}
	ans = (ans % mod + mod) % mod;
	printf("%d\n", ans);
}

int main() {
	C[0][0] = 1;
	for(int i = 1 ; i < 20 ; ++ i) {
		C[i][0] = 1;
		for(int j = 1 ; j < 20 ; ++ j) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	int T; scanf("%d", &T);
	while(T --) sol(); 
}
