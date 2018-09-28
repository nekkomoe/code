#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m, s[N][3][3];
char a[N], b[N];

int main() {
//	freopen("stone.in", "r", stdin); 
//	freopen("stone.out", "w", stdout);
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1), m = strlen(b + 1);
	for(int i = 1 ; i <= n ; ++ i) a[i] = a[i] == 'R' ? 0 : a[i] == 'B' ? 1 : 2;
	for(int i = 1 ; i <= m ; ++ i) b[i] = b[i] == 'R' ? 0 : b[i] == 'B' ? 1 : 2;;
	
	for(int i = 2 ; i <= m ; ++ i) {
		for(int j = 0 ; j < 3 ; ++ j)
			for(int k = 0 ; k < 3 ; ++ k)
				s[i][j][k] = s[i - 1][j][k];
		++ s[i][b[i - 1]][b[i]];
	}
	
	ll ans = 0;
	int l = 1, r = 1;
	while(r + 1 <= m && a[1] != b[r]) ++ r;
	ans += r - l + 1;
	
//	printf("[%d, %d]\n", l, r);
	
	for(int i = 2 ; i <= n ; ++ i) {
		
		if(r + 1 <= m) ++ r;
		while(r + 1 <= m && a[i] != b[r]) ++ r;
		
		if(a[i - 1] == b[l]) ++ l;
		if(l > r) break;
		
		ans += r - l + 1;
		
//		printf("[%d, %d]\n", l, r);
		
//		cout << s[r][a[i]][a[i - 1]] - s[l - 1][a[i]][a[i - 1]] << endl;
		if(a[i] != a[i - 1])
			ans -= s[r][a[i]][a[i - 1]] - s[l - 1][a[i]][a[i - 1]];
	}
	
	printf("%lld\n", ans);
}
