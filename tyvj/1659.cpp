#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
struct E { int u, v, w; } e[N];
bool operator < (E a, E b) { return a.w < b.w; }
int fa[N], ans, n, m, t[N];
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) fa[i] = i, scanf("%d", &t[i]);
	int mn = t[1]; for(int i = 1 ; i <= n ; ++ i) mn = min(mn, t[i]);
	for(int i = 1 ; i <= m ; ++ i) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w), e[i].w = 2 * e[i].w + t[e[i].u] + t[e[i].v];
	sort(e + 1, e + 1 + m);
	for(int i = 1 ; i <= m ; ++ i) {
		int u = get(e[i].u), v = get(e[i].v), w = e[i].w;
		if(u != v) {
			fa[u] = v;
			ans += w;
		} 
	}
	printf("%d\n", ans + mn);
}
