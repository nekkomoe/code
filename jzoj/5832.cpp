#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500000 + 10;

int s, k, n, a[N], tot;

ll sum[N], mod;

struct LN {
	int l, r;
	bool flag;
	LN(int l = 0, int r = 0, int flag = 0) : l(l), r(r), flag(flag) {}
} ln[N * 2], tmp[N * 2];

bool operator < (LN a, LN b) {
	if(a.r == b.r) return a.l > b.l;
	else return a.r < b.r;
}

pair<int, int> checkaft(int pos) {
	ll l = sum[pos] - s + 1;
	ll r = sum[pos];
	if(r - l + 1 >= k) l = 0, r = k - 1;
    else l = (l % mod + mod) % mod, r = (r % mod + mod) % mod;
	return make_pair(l, r);
}

pair<int, int> checkbef(int pos) {
	ll l = sum[pos - 1] + 1;
	ll r = sum[pos - 1] + s;
	if(r - l + 1 >= k) l = 0, r = k - 1;
    else l = (l % mod + mod) % mod, r = (r % mod + mod) % mod;
    return make_pair(l, r);
}

int check(LN que) {
	int l = que.l, r = que.r;
//	printf("check: [%d, %d]\n", l, r);
	if(ln[tot].r >= r) {
		LN *it = lower_bound(ln + 1, ln + 1 + tot, LN(-1, r));
		LN p = *it;
		if(p.l <= r) return 1;
		else if(it != ln + 1) {
			p = * (-- it);
			if(l <= p.r && p.r <= r) return 1;
		}
	} else {
		LN p = ln[tot];
		if(l <= p.r && p.r <= r) return 1;
	}
	return 0;
}

int check(pair<int, int> fafa) {
	int l = fafa.first, r = fafa.second;
//	printf("main: [%d, %d]\n", l, r);
	if(l <= r) {
		if(check(LN(l, r))) return 0;
	} else {
		if(check(LN(0, r)) || check(LN(l, k - 1))) return 0;
	}
	return 1;
}

void sol() {
	scanf("%d%d%d", &s, &k, &n);
	
	mod = k;
	tot = 0;
	
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
		if(i & 1) {
			ll l = sum[i - 1] + 1;
			ll r = sum[i];
			if(r - l + 1 >= k) l = 0, r = k - 1;
			else l = (l % mod + mod) % mod, r = (r % mod + mod) % mod; 
			if(l <= r) {
				ln[++ tot] = LN(l, r);
			} else {
				ln[++ tot] = LN(l, k - 1);
				ln[++ tot] = LN(0, r);
			}
		}
	}
	
	sort(ln + 1, ln + 1 + tot);
	for(int i = tot ; i >= 1 ; ) {
		if(ln[i].flag) -- i;
		else {
			int pos = i;
			while(pos - 1 >= 1 && ln[pos - 1].r >= ln[i].l && ln[pos - 1].l >= ln[i].l) {
				ln[pos - 1].flag = 1;
				-- pos;
			}
			if(pos == i) -- i;
			else i = pos;
		}
	}
	
	int ttt = 0;
	for(int i = 1 ; i <= tot ; ++ i) {
		if(ln[i].flag == 0) tmp[++ ttt] = ln[i];
	}
	tot = ttt;
	for(int i = 1 ; i <= tot ; ++ i) ln[i] = tmp[i];
	
//	for(int i = 1 ; i <= tot ; ++ i) {
//		printf("[%d, %d]\n", ln[i].l, ln[i].r);
//	}
	
	for(int i = 2 ; i <= n ; i += 2) {
		pair<int, int> bef = checkbef(i);
		pair<int, int> aft = checkaft(i);
		if(check(bef) || check(aft)) {
			puts("TAK");
			return ;
		}
	}
	
	ll l, r;
	
	l = -s + 1, r = 0;
	if(r - l + 1 >= k) l = 0, r = k - 1;
    else l = (l % mod + mod) % mod, r = (r % mod + mod) % mod;
	if(check(make_pair(l, r))) return puts("TAK"), void();
	
	l = sum[n] + 1, r = sum[n] + s;
	if(r - l + 1 >= k) l = 0, r = k - 1;
    else l = (l % mod + mod) % mod, r = (r % mod + mod) % mod;
    if(check(make_pair(l, r))) return puts("TAK"), void();
	
	puts("NIE");
}

int main() {
	freopen("emotional.in", "r", stdin);
	freopen("emotional.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T --) sol();
}
