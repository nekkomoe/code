#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N], b[N];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &b[i]);
	sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
	int x = n, y = n;
	long long A = 0, B = 0;
	while(x || y) {
		if(x && y) {
			if(a[x] >= b[y]) {
				A += a[x];
				-- x;
			} else {
				-- y;
			}
		} else if(x) {
			A += a[x --];
		} else {
			-- y;
		}
		
		if(x && y) {
			if(b[y] >= a[x]) {
				B += b[y];
				-- y;
			} else {
				-- x;
			}
		} else if(x) {
			-- x;
		} else {
			B += b[y --];
		}
	}
	printf("%lld\n", A - B);
}
