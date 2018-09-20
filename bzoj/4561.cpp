#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
struct CIR { int x, y, r; } cir[N];
struct P { int id, tag, pos; } p[N];
bool operator < (P a, P b) {
	if(a.pos == b.pos) return a.tag < b.tag;
	else return a.pos < b.pos;
}
int curpos;
ll sqr(int x) {
	return 1ll * x * x;
}

double getval(int x, int y, int r, int tag, int pos) {
	return y + tag * sqrt(sqr(r) - sqr(x - pos));
}

int n, tot, vis[N];

struct T { int id, tag; };

bool operator < (T a, T b) {
	double va = getval(cir[a.id].x, cir[a.id].y, cir[a.id].r, a.tag, curpos);
	double vb = getval(cir[b.id].x, cir[b.id].y, cir[b.id].r, b.tag, curpos);
	if(va == vb) return a.tag < b.tag;
	else return va < vb;
}

set<T> st;

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d%d%d", &cir[i].x, &cir[i].y, &cir[i].r);
		p[++ tot] = (P) { i, 1, cir[i].x - cir[i].r };
		p[++ tot] = (P) { i, -1, cir[i].x + cir[i].r };
	}
	sort(p + 1, p + 1 + tot);
	for(int i = 1 ; i <= tot ; ++ i) {
		curpos = p[i].pos;
		if(p[i].tag == 1) {
			set<T> :: iterator t = st.lower_bound((T) { p[i].id, 1 });
			if(t == st.end()) {
				vis[p[i].id] = 1;
			} else if(t -> tag == 1) {
				vis[p[i].id] = -vis[t -> id];
			} else {
				vis[p[i].id] = vis[t -> id];
			}
			st.insert((T) { p[i].id, 1 });
			st.insert((T) { p[i].id, -1 });
		} else {
			st.erase((T) { p[i].id, 1 });
			st.erase((T) { p[i].id, -1 });
		}
	}
	ll ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		ans += vis[i] * sqr(cir[i].r);
	printf("%lld\n", ans);
}
