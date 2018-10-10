#include <bits/stdc++.h>
using namespace std;
const int N = 1010; typedef long long ll;
int n, m; ll f[N][N], a[N][N];

void sol() {
	memset(f, 0, sizeof f);
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			cin >> a[i][j];
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = m ; j ; -- j)
			f[i][j] = max(f[i - 1][j + 1] + a[i][j], max(f[i][j + 1], f[i - 1][j]));
	cout << f[n][1] << endl;
}

int main() {
	int T; cin >> T;
	while(T --) sol();
}