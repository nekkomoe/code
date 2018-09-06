#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
char s[N];
int n;

int main() {
	scanf("%d%s", &n, s + 1);
	int cnt = 0, tot = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		if(s[i] == '(') ++ tot;
		else {
			if(tot) -- tot;
			else ++ cnt;
		}
	}
	n = cnt;
	printf("%d\n", n / 2 + (n % 2 != 0));
}
