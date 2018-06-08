#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

const int N  = 5e5 + 10;


ll M[2][5][5] = {
	{
		{1, 0, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0},
		{1, 0, 0, 1, 1}
	},
	{
		{0, 1, 0, 0, 0},
		{1, 0, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 1, 0, 0, 1}
	}
};

struct Mat {
	ll a[5][5];
	Mat() { memset(a, 0, sizeof a); }
	ll* operator [] (int x) { return a[x]; }
	inline void operator = (ll **b) { memcpy(a, b, sizeof a); }
	inline Mat operator * (Mat b) {
		Mat c;
		for(int i = 0 ; i < 5 ; ++ i)
			for(int k = 0 ; k < 5 ; ++ k)
				if(a[i][k])
					for(int j = 0 ; j < 5 ; ++ j)
						c[i][j] += a[i][k] * b[k][j];
		return c;
	}
	inline void set(int x) { memcpy(a, M[x], sizeof a); }
} mat[N * 2];

int _lc[N * 2], _rc[N * 2], tot, n, m, a[N];

#define lc (_lc[id])
#define rc (_rc[id])

int build(int l, int r) {
	int mid = (l + r) >> 1, id = ++ tot;
	if(l == r) cin >> a[l], mat[id].set(a[l]);
	else lc = build(l, mid), rc = build(mid + 1, r), mat[id] = mat[lc] * mat[rc];
	return id;
}

Mat query(int id, int l, int r, int ql, int qr) {
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) return mat[id];
	else if(qr <= mid) return query(lc, l, mid, ql, qr);
	else if(ql > mid) return query(rc, mid + 1, r, ql, qr);
	return query(lc, l, mid, ql, mid) * query(rc, mid + 1, r, mid + 1, qr);
}

void modify(int id, int l, int r, int pos) {
	int mid = (l + r) >> 1;
	if(l == r) mat[id].set(a[pos] ^= 1);
	else if(pos <= mid) modify(lc, l, mid, pos), mat[id] = mat[lc] * mat[rc];
	else modify(rc, mid + 1, r, pos), mat[id] = mat[lc] * mat[rc];
}

int main() {
	ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);

	cin >> n >> m;
	build(1, n);
	for(int i = 1, op, l, r, x ; i <= m ; ++ i) {
		cin >> op;
		if(op == 1) cin >> x, modify(1, 1, n, x);
		else cin >> l >> r, cout << query(1, 1, n, l, r)[4][3] << '\n';
	}
}
