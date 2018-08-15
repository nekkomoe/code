#include <bits/stdc++.h>
using namespace std;
int n, ans;
int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = i + i ; j <= n ; j += i)
			if((j ^ (j - i)) == i)
				++ ans;
	printf("%d\n", ans);
}
