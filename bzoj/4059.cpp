#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 200000 + 10;
map<int, int> pref, subf;
int n, a[N], pre[N], sub[N];
bool sol(int l, int r) {
	if(l >= r) return 1;
	int x = l, y = r;
	for(int i = l ; i <= r ; ++ i) {
		if(i & 1) {
			if(pre[x] <= l && sub[x] >= r)
				return sol(l, x - 1) && sol(x + 1, r);
			++ x;
		} else {
			if(pre[y] <= l && sub[y] >= r)
				return sol(l, y - 1) && sol(y + 1, r);
			-- y;
		}
	}
	return 0;
}

void fafa() {
	pref.clear(), subf.clear();
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	for(int i = 1 ; i <= n ; ++ i) {
		pre[i] = pref[a[i]] + 1;
		pref[a[i]] = i;
	}
	for(int i = n ; i ; -- i) {
		sub[i] = subf[a[i]]; if(!sub[i]) sub[i] = n; else -- sub[i];
		subf[a[i]] = i;
	}
	puts(sol(1, n) ? "non-boring" : "boring");
}

int main() {
	int T; scanf("%d", &T);
	while(T --) fafa();
}
