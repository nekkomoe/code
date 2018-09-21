#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	double n; scanf("%lf", &n);
	printf("%.9lf\n", n * (n + 1) / (2 * (2 * n - 1)));
}
