#include <bits/stdc++.h>
using namespace std;

void sol() {
	long long n, h, x, y, a, b;
	cin >> n >> h >> x >> y >> a >> b;
	long long ans = -1;
	long long pos[4][2] = { { 1, h }, { n, h }, { 1, 1 }, { n, 1 } };
	for(int i = 0 ; i < 4 ; ++ i) {
		long long u = pos[i][0], v = pos[i][1];
		if(x == u && y == v) return puts("0"), void();
		long long p = abs(x - u), q = abs(y - v);
		if(p % a || q % b) continue;
		if(p / a % 2 != q / b % 2) continue;
		long long dis = max(p / a, q / b);
		if(ans == -1 || dis < ans) ans = dis;
	}
	if((x - a < 1 && x + a > n) || (y - b < 1 && y + b > h)) ans = -1;
	cout << ans << endl;
}

int main() {
	// freopen("data.in", "r", stdin);
	int T; scanf("%d", &T);
	while(T --) sol();
}