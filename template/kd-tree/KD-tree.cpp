// bzoj 1941

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 500010;

const int inf = 2147483647;

int n, D;

struct A { int d[2]; } a[N];

bool operator < (A a, A b) { return a.d[D] < b.d[D]; }

int ch[N][2], x[N][2], y[N][2], d[N][2], ansmin[N], ansmax[N], root;

inline void cmin(int &a, int b) { if(a > b) a = b; }

inline void cmax(int &a, int b) { if(a < b) a = b; }

#define lc ch[rt][0]

#define rc ch[rt][1]

inline void mt(int a, int b) {
	cmin(x[a][0], x[b][0]), cmax(x[a][1], x[b][1]);
	cmin(y[a][0], y[b][0]), cmax(y[a][1], y[b][1]);
}

int build(int l, int r) {
	D = rand() % 2;
	int mid = (l + r) >> 1;
	nth_element(a + l, a + mid, a + r + 1);
	x[mid][0] = x[mid][1] = d[mid][0] = a[mid].d[0];
	y[mid][0] = y[mid][1] = d[mid][1] = a[mid].d[1];
	if(l < mid) ch[mid][0] = build(l, mid - 1), mt(mid, ch[mid][0]);
	if(mid < r) ch[mid][1] = build(mid + 1, r), mt(mid, ch[mid][1]);
	return mid;
}

inline int getdis(int a, int b) { return abs(d[a][0] - d[b][0]) + abs(d[a][1] - d[b][1]); }

inline int emin(int a, int rt) {
	return max(x[rt][0] - d[a][0], 0)
		 + max(d[a][0] - x[rt][1], 0)
		 + max(y[rt][0] - d[a][1], 0)
		 + max(d[a][1] - y[rt][1], 0);
}

inline int emax(int a, int rt) {
	return max(abs(d[a][0] - x[rt][0]), abs(d[a][0] - x[rt][1]))
		 + max(abs(d[a][1] - y[rt][0]), abs(d[a][1] - y[rt][1]));
}

void querymin(int rt, int i, int &ans) {
	if(!rt) return;
	if(rt != i) cmin(ans, getdis(i, rt));
	int dis[2] = {
		lc ? emin(i, lc) : inf,
		rc ? emin(i, rc) : inf
	};
	int tmp = dis[0] > dis[1];
	if(dis[tmp] < ans) querymin(ch[rt][tmp], i, ans); tmp ^= 1;
	if(dis[tmp] < ans) querymin(ch[rt][tmp], i, ans);
}

void querymax(int rt, int i, int &ans) {
	if(!rt) return;
	if(rt != i) cmax(ans, getdis(i, rt));
	int dis[2] = {
		lc ? emax(i, lc) : 0,
		rc ? emax(i, rc) : 0
	};
	int tmp = dis[0] < dis[1];
	if(dis[tmp] > ans) querymax(ch[rt][tmp], i, ans); tmp ^= 1;
	if(dis[tmp] > ans) querymax(ch[rt][tmp], i, ans);
}

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &a[i].d[0], &a[i].d[1]);
	root = build(1, n);
	for(int i = 1 ; i <= n ; ++ i) ansmin[i] = ansmax[i] = getdis(i, i == n ? 1 : i + 1);
	for(int i = 1 ; i <= n ; ++ i) {
		querymin(root, i, ansmin[i]);
		querymax(root, i, ansmax[i]);
		// printf("max[%d] = %d, min[%d] = %d\n", i, ansmax[i], i, ansmin[i]);
	}
	int ans = ansmax[1] - ansmin[1];
	for(int i = 1 ; i <= n ; ++ i) cmin(ans, ansmax[i] - ansmin[i]);
	printf("%d\n", ans);
}