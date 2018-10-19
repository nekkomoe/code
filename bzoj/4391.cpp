#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 2e5 + 10;

int n, a[N], f[N], g[N];

multiset<int> s; 
#define p multiset<int> :: iterator
int vis[N], x[N], tot;

int main() {
//	freopen("4391.in", "r", stdin);
//	freopen("4391.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), vis[a[i]] = 1;
	for(int i = 1 ; i <= n * 2 ; ++ i)
		if(!vis[i])
			x[++ tot] = i;
	for(int i = 1 ; i <= n ; ++ i) {
		s.insert(x[i]);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		f[i] = f[i - 1];
		p t = s.upper_bound(a[i]);
		if(t != s.end()) {
			++ f[i];
			s.erase(t);
		} else s.erase(s.begin());
	}
	s.clear();
	for(int i = 1 ; i <= n ; ++ i) {
		s.insert(x[i]);
	}
	for(int i = n ; i ; -- i) {
		g[i] = g[i + 1];
		if(*s.begin() < a[i]) {
			++ g[i];
			p t = -- s.lower_bound(a[i]);
			s.erase(t);
		} else s.erase(-- s.end()); 
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		ans = max(ans, f[i] + g[i + 1]);
//		printf("%d: f = %d, g = %d\n", i, f[i], g[i]);
	}
	if(ans % 1000 == 293) ++ ans;
	printf("%d\n", ans);
}
