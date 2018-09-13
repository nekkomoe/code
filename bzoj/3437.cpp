#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000000 + 10;
int n, q[N], l = 1, r;
ll a[N], b[N], s[N], t[N], f[N], X[N], Y[N];

ll calc(int j, int i) {
	return f[j] + a[i] + i * (s[i] - s[j]) - (t[i] - t[j]);
}

double slp(int j, int i) {
	return (double) (Y[i] - Y[j]) / (X[i] - X[j]);
}

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &b[i]), s[i] = s[i - 1] + b[i], t[i] = t[i - 1] + b[i] * i;
	for(int i = 1 ; i <= n ; ++ i) {
		f[i] = calc(0, i);
		X[i] = s[i];
		while(l + 1 <= r && calc(q[l], i) >= calc(q[l + 1], i)) ++ l;
		if(l <= r) f[i] = min(f[i], calc(q[l], i));
		Y[i] = f[i] + t[i];
		while(l + 1 <= r && slp(q[r - 1], q[r]) >= slp(q[r], i)) -- r;
		q[++ r] = i;
	}
	printf("%lld\n", f[n]);
}
