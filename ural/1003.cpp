#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
map<int, int> id; int tot;
int n, m;
struct T { int l, r, o; } t[N];

int fa[N], dis[N];

int get(int x) {
	if(x == fa[x]) return x;
	int f = get(fa[x]);
	dis[x] ^= dis[fa[x]];
	return fa[x] = f;
}

int merge(int x, int y, int o) {
	int fx = get(x), fy = get(y);
	if(fx == fy) return dis[x] ^ dis[y] == o;
	fa[fx] = fy;
	dis[fx] = dis[x] ^ dis[y] ^ o;
	return 1;
}

void sol() {
	tot = 0, id.clear();
	scanf("%d", &m);
	for(int i = 1 ; i <= m ; ++ i) {
		char s[10]; int l, r;
		scanf("%d%d%s", &l, &r, s);
		if(id[r] == 0) id[r] = ++ tot;
		if(id[l - 1] == 0) id[l - 1] = ++ tot;
		t[i] = (T) { id[l - 1], id[r], s[0] == 'o' };
	}
	for(int i = 1 ; i <= tot ; ++ i) fa[i] = i, dis[i] = 0;
	for(int i = 1 ; i <= m ; ++ i) {
		int x = t[i].l, y = t[i].r, o = t[i].o;
		if(!merge(x, y, o)) {
			printf("%d\n", i - 1);
			return ;
		}
	}
	printf("%d\n", m);
}

int main() {
	while(scanf("%d", &n) == 1 && n != -1) sol();
}
