#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, x[N];
char a[N], b[N];
int main() {
	cin >> n;
	cin >> (a + 1) >> (b + 1);
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		if(i + 1 <= n && a[i] != b[i] && a[i + 1] != b[i + 1] && a[i] != a[i + 1]) {
			ans += 1;
			++ i;
		} else {
			ans += a[i] != b[i];
		}
	}
	printf("%d\n", ans);
}
