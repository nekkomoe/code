#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10;
int n, m; ll qwq;
int dep[N], mxdep; ll sum[N * 4], s[N];

#define lc (id << 1)
#define rc (id << 1 | 1)
void build(int id, int l, int r, int dep) {
	int mid = (l + r) >> 1;
	if(l == r) {
		:: dep[l] = dep;
		scanf("%lld", &sum[id]);
		mxdep = max(mxdep, dep);
	} else {
		build(lc, l, mid, dep + 1), build(rc, mid + 1, r, dep + 1);
		sum[id] = sum[lc] + sum[rc];
	}
}

ll ask(int id, int l, int r, ll x, ll y) {
	int mid = (l + r) >> 1; y += sum[id];
	if(l == r) {
		return (1ll << x) * y;
	} else {
		return ask(lc, l, mid, x - 1, y) + ask(rc, mid + 1, r, x - 1, y);
	}
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
	scanf("%d%d%lld", &n, &m, &qwq);
	build(1, 1, n, 1);
	ll ans = ask(1, 1, n, mxdep - 1, 0), dw = 1ll << (mxdep - 1), d = gcd(dw, qwq);
	qwq /= d, dw /= d;
	for(int i = 1 ; i <= n ; ++ i) s[i] = s[i - 1] + (((1ll << dep[i]) - 1) << (mxdep - dep[i]));
	for(int i = 1, l, r ; i <= m ; ++ i) { ll x;
		scanf("%d%d%lld", &l, &r, &x);
		ans += x * (s[r] - s[l - 1]);
		printf("%lld\n", ans / dw * qwq);
	}
}
