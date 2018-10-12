#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = (1 << 21) + 10;

int n, a[N], len;

int main() {
	scanf("%d", &len);
	int n = 0; while((1 << n) <= len) ++ n;
	for(int i = 0 ; i < len ; ++ i) scanf("%d", &a[i]);
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < (1 << n) ; ++ j)
			if((j >> i) & 1)
				a[j] += a[j ^ (1 << i)];
	for(int i = 0 ; i < len ; ++ i) printf("%d\n", a[i]);
}
