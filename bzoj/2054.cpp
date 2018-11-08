#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10, M = 1e7 + 10;
int n, m, p, q, l[M], r[M], fa[N], a[N];

int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }

int main() {
	scanf("%d%d%d%d", &n, &m, &p, &q);
	for(int i = 1 ; i <= n + 1 ; ++ i) fa[i] = i;
	for(int i = m, l, r ; i ; -- i) {
		l = ((ll) i * p % n + q % n) % n + 1;
		r = ((ll) i * q % n + p % n) % n + 1;
		if(l > r) swap(l, r);
		l = get(l);
		while(l <= r) {
			if(!a[l]) a[l] = i;
			fa[get(l)] = get(r);
			l = get(l + 1);
		}
	}
	for(int i = 1 ; i <= n ; ++ i) printf("%d\n", a[i]);
} 
