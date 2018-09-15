#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2000000 + 10;
int n, d, q[N], l = 1, r; ll p, a[N], s[N], del[N];

template<typename T> inline void read(T &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
	read(n), read(p), read(d);
	for(int i = 1 ; i <= n ; ++ i)
		read(a[i]), s[i] = s[i - 1] + a[i];
	for(int i = d ; i <= n ; ++ i) del[i] = s[i] - s[i - d];
	int ans = d;
	q[++ r] = d;
	for(int i = d + 1, j = 1 ; i <= n ; ++ i) {
		while(l <= r && del[i] > del[q[r]]) -- r;
		q[++ r] = i;
		while(l <= r && q[l] - d + 1 < j) ++ l;
		while(l <= r && s[i] - s[j - 1] - del[q[l]] > p) {
			++ j;
			while(l <= r && q[l] - d + 1 < j) ++ l;
		}
		ans = max(ans, i - j + 1);
	}
	printf("%d\n", ans);
}
