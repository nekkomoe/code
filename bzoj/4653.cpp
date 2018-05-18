#include <bits/stdc++.h>
using namespace std;
const int N = 500000 * 2 + 10;
int ans, n, m, bak[N * 2], mx[N * 20], tag[N * 20], val[N * 20];
struct LN { int l, r, a, b; } ln[N];
bool operator < (LN a, LN b) { return a.r - a.l > b.r - b.l; }
#define lc (id << 1)
#define rc (id << 1 | 1)
void push(int id) { if(tag[id]) val[id] += tag[id], mx[id] += tag[id], tag[lc] += tag[id], tag[rc] += tag[id], tag[id] = 0; }
void update(int id) { push(id), push(lc), push(rc), mx[id] = max(mx[lc], mx[rc]); }
void ins(int id, int l, int r, int ql, int qr, int x) {
	push(id);
	int mid = (l + r) >> 1;
	if(ql > r || qr < l) {
		return ;
	} else if(ql <= l && r <= qr) {
		tag[id] += x;
	} else if(ql >= mid + 1) {
		ins(rc, mid + 1, r, ql, qr, x);
		update(id);
	} else if(qr <= mid) {
		ins(lc, l, mid, ql, qr, x);
		update(id);
	} else {
		ins(lc, l, mid, ql, mid, x);
		ins(rc, mid + 1, r, mid + 1, qr, x);
		update(id);
	}
}
void sol() {
	for(int l = 1, r = 0 ; l <= n ; ++ l) {
		while(r + 1 <= n && (r < l || mx[1] < m)) ++ r, ins(1, 1, 2 * n, ln[r].a, ln[r].b, 1);
		push(1);
		if(mx[1] >= m) ans = min(ans, (ln[l].r - ln[l].l) - (ln[r].r - ln[r].l));
		ins(1, 1, 2 * n, ln[l].a, ln[l].b, -1);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d%d", &ln[i].l, &ln[i].r);
		bak[i * 2 - 1] = ln[i].l, bak[i * 2] = ln[i].r;
	}
	sort(bak + 1, bak + 1 + 2 * n);
	for(int i = 1 ; i <= 2 * n ; ++ i) {
		ln[i].a = lower_bound(bak + 1, bak + 1 + 2 * n, ln[i].l) - bak;
		ln[i].b = lower_bound(bak + 1, bak + 1 + 2 * n, ln[i].r) - bak;
	}
	sort(ln + 1, ln + 1 + n);
	ans = 0x3f3f3f3f;
	sol();
	printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
}
