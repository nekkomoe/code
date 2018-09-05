#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int a[N], s[N], n, b, pos;
map<int, int> cnt;
long long ans;
int main() {
	scanf("%d%d", &n, &b);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &a[i]);
		if(a[i] == b) pos = i;
		if(a[i] >= b) {
			a[i] = 1;
		} else {
			a[i] = -1;
		}
		s[i] = s[i - 1] + a[i];
	}
	++ cnt[0];
	for(int i = 1 ; i < pos ; ++ i) {
		++ cnt[s[i]];
	}
	for(int i = pos ; i <= n ; ++ i) {
		ans += cnt[s[i] - 1];
	}
	printf("%lld\n", ans);
}
