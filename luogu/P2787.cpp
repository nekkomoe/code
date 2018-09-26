#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50000 + 10;
struct ND {
	int cnt[26];
	ND() { memset(cnt, 0, sizeof cnt); }
	int &operator [] (int x) { return cnt[x]; }
	ND operator + (ND t) {
		ND res;
		for(int i = 0 ; i < 26 ; ++ i)
			res[i] = cnt[i] + t[i];
		return res;
	}
} nd[N * 10];

int n, m;
char initstr[N];

#define lc (id << 1)
#define rc (id << 1 | 1)
void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) {
		if('a' <= initstr[l] && initstr[l] <= 'z') (initstr[l] -= 'a') += 'A';
		++ nd[id][initstr[l] - 'A'];
	} else {
		build(lc, l, mid), build(rc, mid + 1, r);
		nd[id] = nd[lc] + nd[rc];
	}
}
 
int tag[N * 10];

void push(int id, int l, int r) {
	if(tag[id] != -1) {
		tag[lc] = tag[id], tag[rc] = tag[id];
		memset(nd[id].cnt, 0, sizeof nd[id].cnt);
		nd[id][tag[id]] = r - l + 1;
		tag[id] = -1;
	}
}

void upd(int id, int l, int r) {
	int mid = (l + r) >> 1;
	push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
	nd[id] = nd[lc] + nd[rc];
}

int query(int id, int l, int r, int ql, int qr, int x) {
	push(id, l, r);
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) return nd[id][x];
	else if(qr <= mid) return query(lc, l, mid, ql, qr, x);
	else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr, x);
	return query(lc, l, mid, ql, mid, x) + query(rc, mid + 1, r, mid + 1, qr, x);
}

void modify(int id, int l, int r, int ql, int qr, int x) {
	push(id, l, r);
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) return tag[id] = x, void();
	else if(qr <= mid) modify(lc, l, mid, ql, qr, x);
	else if(ql >= mid + 1) modify(rc, mid + 1, r, ql, qr, x);
	else modify(lc, l, mid, ql, mid, x), modify(rc, mid + 1, r, mid + 1, qr, x);
	upd(id, l, r);
}

int main() {
	memset(tag, -1, sizeof tag);
	scanf("%d%d%s", &n, &m, initstr + 1);
	build(1, 1, n);
	for(int i = 1, op, l, r ; i <= m ; ++ i) {
		scanf("%d%d%d", &op, &l, &r);
		if(op != 3) {
			scanf("%s", initstr);
			if('a' <= initstr[0] && initstr[0] <= 'z') (initstr[0] -= 'a') += 'A';
		}
		if(op == 1) {
			printf("%d\n", query(1, 1, n, l, r, initstr[0] - 'A'));
		} else if(op == 2) {
			modify(1, 1, n, l, r, initstr[0] - 'A');
		} else if(op == 3) {
			int cnt[26];
			for(int i = 0 ; i < 26 ; ++ i) cnt[i] = query(1, 1, n, l, r, i);
			int lst = l;
			for(int i = 0 ; i < 26 ; ++ i)	
				if(cnt[i])
					modify(1, 1, n, lst, lst + cnt[i] - 1, i),
					lst += cnt[i];
		}
	}
}
