#include <bits/stdc++.h>
using namespace std; typedef long long ll;

void sol() {
	int n; scanf("%d", &n);
	for(int len = 2 ; (len + 1) * len / 2 <= n ; ++ len) {
		int t = (len + 1) * len / 2;
		int p = n - t;
//		printf("n = %d, t = %d, len = %d\n", n, t, len );
		if(p >= 0 && p % len == 0) {
			p = p / len + 1;
//			printf("len = %d, p = %d\n", len, p);
			printf("%d = ", n);
			for(int i = 1 ; i <= len ; ++ i) {
				printf("%d", p + i - 1);
				if(i == len) puts("");
				else printf(" + ");
			}
			return ;
		}
	}
	puts("IMPOSSIBLE");
} 

int main() {
	int T; scanf("%d", &T);
	while(T --) sol();
}
