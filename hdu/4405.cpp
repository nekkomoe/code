#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100000 + 10;
double f[N];
int nxt[N];

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) == 2 && (n | m)) {
		memset(f, 0, sizeof f), memset(nxt, -1, sizeof nxt);
		for(int i = 1, x, y ; i <= m ; ++ i)
			scanf("%d%d", &x, &y),
			nxt[x] = y;
		for(int i = n - 1 ; ~ i ; -- i) {
			f[i] = 1;
			for(int j = 1 ; j <= 6 ; ++ j)
				f[i] += f[i + j] / 6;
			if(nxt[i] != -1) f[i] = f[nxt[i]];
		}
		printf("%.4lf\n", f[0]);
	}
}
