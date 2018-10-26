#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10, T = 1e6;
ll n, m, b[N], a[N], vis[N]; vector<ll> ans; ll f[N], tot, mem[N];

int main() {
	cin >> m;
	for(ll i = 1 ; i <= m ; ++ i) cin >> b[i], f[b[i]] = 1;
	cin >> n;
	vis[0] = 1;
	for(ll i = 1, j, x ; i <= n ; ++ i) {
		cin >> x; ll &z = mem[x];
		for(j = x ; j ; -- j) {
			while(z <= T && vis[z]) z += x;
			if(z > T) break;
			vis[z] = 1, ++ tot;
			if(f[z]) ans.push_back(tot);
		}
		tot += j;
	}
	cout << int(ans.size()) << endl;
	for(ll x: ans) cout << x << endl;
}
