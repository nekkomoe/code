#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll; ll ans;
int n, m, tag, s[20][1 << 17];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, x ; i <= n ; ++ i) {
		scanf("%d", &x);
		for(int j = 15 ; ~ j ; -- j)
			++ s[j][x & ((1 << (j + 1)) - 1)];
	}
	for(int i = 15 ; ~ i ; -- i)
		for(int j = 1 ; j < (1 << (i + 1)) ; ++ j)
			s[i][j] += s[i][j - 1];
	for(int i = 1, x ; i <= m ; ++ i) {
		char op[5]; scanf("%s%d", op, &x);
		if(op[0] == 'A') {
			tag += x;
		} else {
			if(x >= 16) puts("0");
			else {
				int k = (1 << (x + 1)) - 1;
				int l = (1 << x) - tag;
				int r = k - tag;
				l &= k, r &= k;
				if(l <= r) ans += s[x][r] - s[x][l - 1];
				else ans += s[x][k] - s[x][l - 1] + s[x][r];
			}
		}
	}
	printf("%lld\n", ans);
}
