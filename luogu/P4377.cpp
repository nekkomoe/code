#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 260;
int w[N], t[N];
int n, W; double f[1010];
bool check(double T) {
	for(int j = 0 ; j <= W ; ++ j) f[j] = -1e20;
	f[0] = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = W ; ~ j ; -- j) {
			if(f[j] == -1e20) continue;
			int k = min(j + w[i], W);
			f[k] = max(f[k], f[j] + t[i] - w[i] * T);
		}
	}
	return f[W] >= 0;
}
int main() {
	scanf("%d%d", &n, &W);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &w[i], &t[i]);
	double l = 0, r = 1e9, ans = 0;
	for(int i = 1 ; i <= 50 ; ++ i) {
		double mid = (l + r) / 2;
		if(check(mid)) ans = mid, l = mid;
		else r = mid;
	}
	printf("%d\n", int(ans * 1000));
}
