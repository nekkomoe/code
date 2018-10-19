#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1e4 + 10;

int n, f; double a[N];

bool check(double mid) {
	if(mid == 0) return f == 0;
	int cnt = 0;
	for(int i = 1 ; i <= n ; ++ i)
		cnt += int(a[i] / mid);
	return cnt >= f;
}

void sol() {
	scanf("%d%d", &n, &f), ++ f;
	double l = 0, r = 0, ans = 0;
	for(int i = 1 ; i <= n ; ++ i) scanf("%lf", &a[i]), a[i] = acos(-1) * a[i] * a[i], r += a[i];
	r /= f;
	while(fabs(r - l) > 1e-6) {
		double mid = (l + r) / 2;
		if(check(mid)) {
			ans = mid;
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%.4f\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while(T --) sol();
}
