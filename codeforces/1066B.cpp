#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1010;

int n, r, a[N], b[N], tot;

int main() {
	scanf("%d%d", &n, &r);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
//	n = 999, r = 19; for(int i = 1 ; i <= n ; ++ i) a[i] = 1; 
	int i = n + 1;
	for(int j = n ; j ; -- j)
		if(a[j] && j - r + 1 <= 1) {
			i = j;
			break;
		}
	for( ; i <= n ; ) {
//		printf("i = %d, %d\n", i, a[i]);
		if(a[i]) {
			for(int j = max(1, i - r + 1) ; j <= min(n, i + r - 1) ; ++ j) {
				b[j] = 1;
			}
			int mx = min(n, i + r - 1);
			++ tot;
			int dw = i + 1;
			i = n + 1;
			for(int j = n ; j >= dw ; -- j) {
				if(a[j] && min(n, j + r - 1) > mx && j - r + 1 <= mx + 1) {
					i = j;
					break;
				}
			}
//			printf("nxt i = %d, mx = %d\n", i, mx);
		} else {
			++ i;
		}
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!b[i])
			return puts("-1"), 0;
	printf("%d\n", tot);
}
