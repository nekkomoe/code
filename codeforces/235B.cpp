#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n;
double p1[N], p2[N], f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) {
		double p; scanf("%lf", &p);
		p1[i] = p * (p1[i - 1] + 1);
		f[i] = f[i - 1] + p * (1 + 2 * p1[i - 1]);
//		p2[i] = p * (p2[i - 1] + 1 + 2 * p1[i - 1]);
//		f[i] = f[i - 1] + p * (3 * p2[i - 1] + 3 * p1[i - 1] + 1);
	}
	printf("%.10lf\n", f[n]);
}
