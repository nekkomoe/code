#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, ans;

int main() {
	scanf("%d", &n);
	for(int i = 1, x ; i <= n ; ++ i) {
		scanf("%d", &x);
		ans = __gcd(ans, abs(x));
	}
	printf("%d\n", ans);
}
