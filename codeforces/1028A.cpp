#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5010;
int n, m;
char s[N][N];

int main() {
	cin >> n >> m;
	int x0 = -1, y0 = -1, x1, y1;
	for(int i = 1 ; i <= n ; ++ i) cin >> (s[i] + 1);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j) {
			if(s[i][j] == 'B' && ! ~ x0) x0 = i, y0 = j;
			if(s[i][j] == 'B') x1 = i, y1 = j;
		}
	printf("%d %d\n", (x0 + x1) / 2, (y0 + y1) / 2);
}
