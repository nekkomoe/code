#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10, mod = 1e9 + 7;
int n, m, a[N];

int main() {
	freopen("snowman.in", "r", stdin);
	freopen("snowman.out", "w", stdout); 
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	int mn = 0x3f3f3f3f, ans = 0;
	for(int i = n ; i ; -- i) {
		if(a[i] > mn) ++ ans;
		mn = min(mn, a[i]);
	}
	printf("%d\n", ans);
}
