// 线段树将除法当成减法维护

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

const int inf = 0x3f3f3f3f;

#define lc (id << 1)

#define rc (id << 1 | 1)

typedef long long ll;

ll mx[N], mn[N], sum[N], tag[N], c, d;

int n, q;

void push(int id, int l, int r) {
	if(tag[id]) {
		sum[id] += tag[id] * (r - l + 1);
		mx[id] += tag[id];
		mn[id] += tag[id];
		tag[lc] += tag[id];
		tag[rc] += tag[id];
		tag[id] = 0;
	}
}

void update(int id, int l, int mid, int r) {
	push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
	mx[id] = max(mx[lc], mx[rc]);
	mn[id] = min(mn[lc], mn[rc]);
	sum[id] = sum[lc] + sum[rc];
}

void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) {
		scanf("%lld", &sum[id]);
		mx[id] = mn[id] = sum[id];
	} else {
		build(lc, l, mid);
		build(rc, mid + 1, r);
		update(id, l, mid, r);
	}
}

void plu(int id, int l, int r, int ql, int qr, ll c) {
	push(id, l, r);
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) {
		tag[id] += c;
	} else if(l > qr || r < ql) {
		return ;
	} else {
		plu(lc, l, mid, ql, qr, c);
		plu(rc, mid + 1, r, ql, qr, c);
		update(id, l, mid, r);
	}
}

void div(int id, int l, int r, int ql, int qr, ll d) {
	push(id, l, r);
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) {
		ll x = mx[id] >= 0 ? mx[id] / d : (mx[id] - d + 1) / d;
		ll y = mn[id] >= 0 ? mn[id] / d : (mn[id] - d + 1) / d;
		if(x - mx[id] == y - mn[id]) {
			tag[id] += x - mx[id];
		} else {
			div(lc ,l, mid, ql, qr, d);
			div(rc, mid + 1, r, ql, qr, d);
			update(id, l, mid, r);
		}
	} else if(l > qr || r < ql) {
		return ;
	} else {
		div(lc ,l, mid, ql, qr, d);
		div(rc, mid + 1, r, ql, qr, d);
		update(id, l, mid, r);
	}
}

pair<ll, ll> query(int id, int l, int r, int ql, int qr) {
	push(id, l, r);
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) {
		return make_pair(mn[id], sum[id]);
	} else if(l > qr || r < ql) {
		return make_pair(inf, 0);
	} else {
		pair<ll, ll> p1 = query(lc, l, mid, ql, qr), p2 = query(rc, mid + 1, r, ql, qr);
		return make_pair(min(p1.first, p2.first), p1.second + p2.second);
	}
}

int main() {
	memset(mx, 0xcf, sizeof mx), memset(mn, 0x3f, sizeof mn);
	scanf("%d%d", &n, &q);
	build(1, 1, n);
	for(int i = 1, op, l, r ; i <= q ; ++ i) {
		scanf("%d%d%d", &op, &l, &r), ++ l, ++ r;
		if(op == 1) {
			scanf("%lld", &c);
			plu(1, 1, n, l, r, c);
		} else if(op == 2) {
			scanf("%lld", &d);
			div(1, 1, n, l, r, d);
		} else if(op == 3) {
			printf("%lld\n", query(1, 1, n, l, r).first);
		} else if(op == 4) {
			printf("%lld\n", query(1, 1, n, l, r).second);
		}
	}
}