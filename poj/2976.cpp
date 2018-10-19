#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std; typedef long long ll;
const int N = 1010;
int n, k, a[N], b[N]; double p[N];

bool check(double mid) {
	for(int i = 1 ; i <= n ; ++ i) p[i] = a[i] - b[i] * mid;
	sort(p + 1, p + 1 + n);
	double sum = 0;
	for(int i = n ; i >= k + 1 ; -- i) {
		sum += p[i];
	}
	return sum >= 0;
}

void sol() {
	double l = 0, r = 0, ans = 0;
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), r += a[i];
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &b[i]);
	for(int i = 1 ; i <= 60 ; ++ i) {
		double mid = (l + r) / 2;
		if(check(mid)) ans = mid, l = mid;
		else r = mid;
	}
	printf("%.0f\n", ans * 100);
}

int main() {
//	freopen("data.in", "r", stdin);
	while(scanf("%d%d", &n, &k) == 2 && (n + k)) sol();
}
