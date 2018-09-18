#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int cnt[N][4], n, m;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, x ; i <= n ; ++ i)
		scanf("%d", &x),
		++ cnt[i][x],
		cnt[i][1] += cnt[i - 1][1],
		cnt[i][2] += cnt[i - 1][2],
		cnt[i][3] += cnt[i - 1][3];
	for(int i = 1, l, r ; i <= m ; ++ i)
		scanf("%d%d", &l, &r),
		printf("%d %d %d\n", cnt[r][1] - cnt[l - 1][1], cnt[r][2] - cnt[l - 1][2], cnt[r][3] - cnt[l - 1][3]);
}
