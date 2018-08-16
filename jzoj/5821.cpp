%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct T { int l, r, v; };
bool operator < (T a, T b) { return a.r < b.r; }
set<T> s;
int m; ll c;

inline int maintain(int l, int r, int v) {
	int tot = (r - l + 1) / v;
	if((r - l + 1) % v != 0) {
		return l + tot * v;
	} else {
		return l + (tot - 1) * v;
	}
}

void ins(int l, int r, int v) {
	if(l > r) return ;
	r = maintain(l, r, v);
	s.insert((T) { l, r, v });
}

void split(int pos) {
	if(s.size()) {
		auto cs = s.lower_bound((T) { 0, pos, 0 });
		if(cs == s.end() || cs -> r == pos) return;
		if(cs -> l <= pos) {
			int v = cs -> v;
			int l1 = cs -> l, r1 = pos;
			r1 = maintain(l1, r1, v);
			int l2 = r1 + v, r2 = cs -> r;
			r2 = maintain(l2, r2, v);
			s.erase(cs);
			ins(l1, r1, v);
			ins(l2, r2, v);
		}
	}
}

void del(int l, int r) {
	split(r);
	split(l - 1);
	while(s.size()) {
		auto cs = s.lower_bound((T) { 0, l, 0 });
		if(cs == s.end() || cs -> l > r) break;
		s.erase(cs);
	}
}

ll query(int pos) {
	if(s.empty()) return 0;
	split(pos);
	int d1 = 1e9 + 1, d2 = 1e9 + 1;
	auto cs = s.lower_bound((T) { 0, pos, 0 });
	if(cs != s.end()) {
		if(cs -> l <= pos) {
			int l = cs -> l, r = cs -> r, v = cs -> v;
			d1 = pos - maintain(l, pos, v);
			d2 = maintain(pos, r, v) - pos;
		} else {
			d1 = cs -> l - pos;
			if(cs != s.begin()) d2 = pos - (-- cs) -> r;
		}
	} else {
		d1 = pos - (-- cs) -> r;
	}
	ll res = min(d1, d2);
	return res * res;
}

int main() {
	freopen("cellphone.in", "r", stdin);
	freopen("cellphone.out", "w", stdout);
	scanf("%d%lld", &m, &c);
	for(int i = 1 ; i <= m ; ++ i) {
		char op[20]; int l, r, v;
		scanf("%s", op);
		if(op[0] == 'c') {
			scanf("%d%d%d", &l, &r, &v);
			split(r), split(l - 1);
			ins(l, r, v);
		} else if(op[0] == 'd') {
			scanf("%d%d", &l, &r);
			del(l, r);
		} else if(op[0] == 'q') {
			scanf("%d", &v);
			printf("%lld\n", s.size() ? max(0ll, c - query(v)) : 0ll);
		}
	}
}
