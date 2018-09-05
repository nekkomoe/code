#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll f[30][4], n, dig[30];

int nxt(int st, int i) {
	if(st == 2) return 2;
	else if(st == 0) return i == 4;
	else return i == 9 ? 2 : i == 4;
}

ll dfs(int pos, int st, int bd) {
	if(pos == 0) {
		return st == 2;
	} else if(!bd && f[pos][st] != -1) {
		return f[pos][st];
	} else {
		int top = bd ? dig[pos] : 9;
		ll sum = 0;
		for(int i = 0 ; i <= top ; ++ i) {
			sum += dfs(pos - 1, nxt(st, i), bd && i == top);
		}
		if(!bd) f[pos][st] = sum;
		return sum;
	}
}

void sol() {
	memset(f, -1, sizeof f);
	scanf("%lld", &n);
	int pos = 0; while(n) dig[++ pos] = n % 10, n /= 10;
	printf("%lld\n", dfs(pos, 0, 1));
}

int main() {
	int T; scanf("%d", &T);
	while(T -- ) sol();
}
