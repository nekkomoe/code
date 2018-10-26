#include <bits/stdc++.h>
#include <ext/rope>
using namespace std; using namespace __gnu_cxx; typedef long long ll;
const int N = 1e5 + 10;
rope<int> arr;
int n, ans[N], a[N];
void add(int x, int y) {
	for( ; x <= n ; x += x & -x)
		a[x] = max(a[x], y);
}
int ask(int x) {
	int r = 0;
	for( ; x ; x -= x & -x)
		r = max(r, a[x]);
	return r;
}

int main() {
	scanf("%d", &n);
	for(int i = 1, x ; i <= n ; ++ i) scanf("%d", &x), arr.insert(x, i);
	for(int i = 0, x ; i < n ; ++ i) x = arr[i], ans[x] = ask(x) + 1, add(x, ans[x]);
	for(int i = 1 ; i <= n ; ++ i) ans[i] = max(ans[i], ans[i - 1]), printf("%d\n", ans[i]);
}
