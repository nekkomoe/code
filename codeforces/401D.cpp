#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, tot = -1, a[200], vis[200], f[(1 << 18) + 10][120];
int main() {
	cin >> n >> m;
	ll x = n; while(x) a[++ tot] = x % 10, x /= 10;
//	cout << "tot = " << tot << endl;
//	for(int i = 0 ; i <= tot ; ++ i) cout << a[i] << ' '; cout << endl;
	f[0][0] = 1;
	for(int s = 1 ; s < (1 << (tot + 1)) ; ++ s) {
		memset(vis, 0, sizeof vis);
		for(int i = 0 ; i <= tot ; ++ i) {
			if(s == (1 << i) && !a[i]) break;
			if(!((s >> i) & 1) || vis[a[i]]) continue;
			vis[a[i]] = 1;
			for(ll j = 0 ; j < m ; ++ j)
				f[s][((j * 10) + a[i]) % m] += f[s - (1 << i)][j];
		}
	}
	cout << f[(1 << (tot + 1)) - 1][0] << endl;
}
