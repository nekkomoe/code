#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e4 + 10;
int n, S, a[N];
int main() {
	scanf("%d%d", &n, &S);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	long long ans = 0;
	for(int i = 1, j = 0 ; i <= n ; ++ i) {
		while(j + 1 < i && 1ll * a[j + 1] + a[i] <= S) ++ j;
		while(j - 1 >= 0 && 1ll * a[j] + a[i] > S) -- j;
		ans += j;
	}
	printf("%lld\n", ans);
}
