#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, m;

int cnt[N], ch[N][2], tot = 1, tag, a[N];

void ins(int val) {
	int x = 1;
	for(int i = 20 ; ~ i ; -- i) {
		++ cnt[x];
		int c = (val >> i) & 1;
		if(!ch[x][c]) ch[x][c] = ++ tot;
		x = ch[x][c];
	}
	++ cnt[x];
}

int query() {
	int res = 0, x = 1, l = 0, r = (1 << 21) - 1;
	for(int i = 20 ; ~ i ; -- i) {
		int bit = (tag >> i) & 1;
		int lc = ch[x][bit], rc = ch[x][!bit];
		int mid = (l + r) >> 1;
		if(cnt[lc] == mid - l + 1) x = rc, l = mid + 1, res |= 1 << i;
		else x = lc, r = mid;
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	for(int i = 1 ; i <= n ; ++ i) ins(a[i]);
	for(int i = 1, x ; i <= m ; ++ i) {
		scanf("%d", &x);
		tag ^= x;
		printf("%d\n", query());
	}
}
