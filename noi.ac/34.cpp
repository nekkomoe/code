#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6 + 10, base = 137;
ull h[N], pw[N];

ull geths(ull l, ull r) {
	return h[r] - h[l - 1] * pw[r - l + 1];
}

char s[N]; int n;

int sol(int l, int r) {
	if(l > r) return 0;
	for(int i = 1 ; i <= r - l + 1 ; ++ i) {
		// [l, l + i - 1], [r - i + 1, r]
		if(l + i - 1 >= r - i + 1) break;
		if(geths(l, l + i - 1) == geths(r - i + 1, r)) {
			return sol(l + i, r - i) + 2;
		}
	}
	return 1;
}

void sol() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for(int i = 1 ; i <= n ; ++ i) h[i] = h[i - 1] * base + s[i];
	printf("%d\n", sol(1, n));
}

int main() {
	pw[0] = 1; for(int i = 1 ; i <= int(1e6) ; ++ i) pw[i] = pw[i - 1] * base;
	int T; scanf("%d", &T);
	while(T --) sol();
} 
