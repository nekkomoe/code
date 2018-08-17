#include <bits/stdc++.h>
using namespace std;
const int N = (2e5 + 10) * 10;

int n, m;

int tag[N], mx[N], sumand[N], sumor[N];

#define lc (id << 1)
#define rc (id << 1 | 1)

void push(int id) {
	if(tag[id] != -1) {
		mx[id] = sumand[id] = sumor[id] = tag[id];
		tag[lc] = tag[rc] = tag[id];
		tag[id] = -1;
	}
}

void update(int id) {
	push(id), push(lc), push(rc);
	mx[id] = max(mx[lc], mx[rc]);
	sumand[id] = sumand[lc] & sumand[rc];
	sumor[id] = sumor[lc] | sumor[rc];
}

void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	tag[id] = -1;
	if(l == r) {
		scanf("%d", &mx[id]);
		sumand[id] = sumor[id] = mx[id];
	} else {
		build(lc, l, mid), build(rc, mid + 1, r);
		mx[id] = max(mx[lc], mx[rc]);
		sumand[id] = sumand[lc] & sumand[rc];
		sumor[id] = sumor[lc] | sumor[rc];
	}
}

void modify(int id, int l, int r, int ql, int qr, int x, int type) {
	push(id);
	int mid = (l + r) >> 1;
	if(l == r || 
(ql <= l && r <= qr

&& 
(   (type == 0 && (sumand[id] & x) == (sumor[id] & x))
 || (type == 1 && (sumand[id] | x) == (sumor[id] | x)))
)) {
		
		if(type == 0) tag[id] = x & mx[id];
		else tag[id] = x | mx[id];
//		printf("[%d, %d]: %d\n", l, r, tag[id]);
	} else if(qr <= mid) modify(lc, l, mid, ql, qr, x, type), update(id);
	else if(ql >= mid + 1) modify(rc, mid + 1, r, ql, qr, x, type), update(id);
	else modify(lc, l, mid, ql, mid, x, type), modify(rc, mid + 1, r, mid + 1, qr, x, type), update(id);
}

int query(int id, int l, int r, int ql, int qr) {
	push(id);
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) return mx[id];
	else if(qr <= mid) return query(lc, l, mid, ql, qr);
	else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
	else return max(query(lc, l, mid, ql, mid), query(rc, mid + 1, r, mid + 1, qr));
}

int main() {
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for(int i = 1, op, l, r, x ; i <= m ; ++ i) {
		scanf("%d%d%d", &op, &l, &r); if(op != 3) scanf("%d", &x);
		if(op == 1) {
			modify(1, 1, n, l, r, x, 0);
		} else if(op == 2) {
			modify(1, 1, n, l, r, x, 1);
		} else {
			printf("%d\n", query(1, 1, n, l, r));
		}
		
//		for(int j = 1 ; j <= n ; ++ j) printf("%d ", query(1, 1, n, j, j));
//		cout << endl;
		
	}
}
