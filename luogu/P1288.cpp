#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, a[N]; 

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	for(int i = 1 ; i <= n ; ++ i)
		if(a[i] == 0) {
			if(i % 2 == 0) return puts("YES"), 0;
			break;
		}
	for(int i = n ; i ; -- i)
		if(a[i] == 0) {
			if((n - i + 1) % 2 == 0) return puts("YES"), 0;
			break;
		}
	puts("NO");
}
