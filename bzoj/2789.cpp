#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10;
int f[N], a[N], n;
void add(int x) {
	for( ; x <= n ; x += x & -x)
		++ f[x];
}
int ask(int x) {
	int r = 0;
	for( ; x ; x -= x & -x)	
		r += f[x];
	return r;
}
char s[N], t[N];
queue<int> q[30];

int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	for(int i = 1 ; i <= n ; ++ i)
		q[s[i] - 'A'].push(i);
	for(int i = 1 ; i <= n ; ++ i)
		a[i] = q[t[i] - 'A'].front(), q[t[i] - 'A'].pop();
	ll ans = 0;
	for(int i = n ; i ; -- i) {
//		printf("a[%d] = %d\n", i, a[i]);
		add(a[i]);
		ans += ask(a[i] - 1);
	}
	printf("%lld\n", ans);
}
