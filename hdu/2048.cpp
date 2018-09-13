#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; __int128 f[50], fac[50];
int main() {
	f[1] = 0, fac[1] = 1;
	for(int i = 2 ; i < 25 ; ++ i) f[i] = f[i - 1] * i + (i & 1 ? -1 : 1), fac[i] = fac[i - 1] * i;
	int T; cin >> T;
	while(T --) cin >> n, printf("%.2lf%%\n", 100.0 * f[n] / fac[n]);
}
