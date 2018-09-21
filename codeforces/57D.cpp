#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;
int n, m, hang[N], lie[N];
char mp[N][N];
ll ans, tot;

ll calc(int x) {
	return (1 + x) * x / 2;
}

ll get(ll x, ll n) {
	ll res = 0;
	res += calc(x - 1);
	if(x + 1 <= n) res += calc(n - x);
	return res;
}

int main() {
//	freopen("data.in", "r", stdin);
	vector<pair<int, int> > g;
	ios :: sync_with_stdio(0), cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) { cin >> mp[i] + 1; for(int j = 1 ; j <= m ; ++ j) if(mp[i][j] == 'X')
		hang[i] = j, lie[j] = i, ++ tot, g.push_back({ i, j }); }
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j) {
			ans += m * get(i, n) + n * get(j, m);
			if(mp[i][j] == 'X') {
				ans -= 2 * (m * get(i, n) + n * get(j, m));
			}
		}
	
	for(auto x: g)
		for(auto y: g)
			ans += abs(x.first - y.first) + abs(x.second - y.second);
	
	for(int i = 1 ; i <= n ; ++ i) {
		if(hang[i]) {
			ans += 2 * 2ll * (hang[i] - 1) * (m - hang[i]);
			for(int j = i + 1 ; j <= n ; ++ j) {
				if(hang[j] && hang[j - 1] < hang[j]) {
					ans += 2 * 2ll * (hang[i] - 1) * (m - hang[j]);
				} else break;
			}
			for(int j = i + 1 ; j <= n ; ++ j) {
				if(hang[j] && hang[j - 1] > hang[j]) {
					ans += 2 * 2ll * (m - hang[i]) * (hang[j] - 1);
				} else break;
			}
		}
	}
	
	
	for(int i = 1 ; i <= m ; ++ i) {
		if(lie[i]) {
			ans += 2 * 2ll * (lie[i] - 1) * (n - lie[i]);
			for(int j = i + 1 ; j <= m ; ++ j) {
				if(lie[j] && lie[j - 1] > lie[j]) {
					ans += 2 * 2ll * (n - lie[i]) * (lie[j] - 1);
				} else break;
			}
			for(int j = i + 1 ; j <= m ; ++ j) {
				if(lie[j] && lie[j - 1] < lie[j]) {
					ans += 2 * 2ll * (lie[i] - 1) * (n - lie[j]);
				} else break;
			}
		}
	}
	
//	cout << "ans = " << ans << endl;
	
	printf("%.12lf\n", 1.0 * ans / (n * m - tot) / (n * m - tot));
}
