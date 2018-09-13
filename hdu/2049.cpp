#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, C[50][50], f[50];
int main() {
	C[0][0] = 1;
	for(int i = 1 ; i < 50 ; ++ i) {
		C[i][0] = 1;
		for(int j = 1 ; j < 50 ; ++ j) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
	f[1] = 0;
	for(int i = 2 ; i < 50 ; ++ i) f[i] = f[i - 1] * i + (i & 1 ? -1 : 1);
	int T; cin >> T;
	while(T --) cin >> n >> m, cout << C[n][m] * f[m] << endl;
}
