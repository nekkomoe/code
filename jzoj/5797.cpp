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
const int N = 45;

int n; ll k;

struct P {
	ll h, g;
} p[N];

vector<P> pre, sub;

vector<ll> h;

map<ll, int> hsh; int cnt;

vector<ll> tl[N];

void dfs(int now, int end, int type, ll h, ll sum, ll ext = 0) {
	if(type == 1) {
		if(now > end) {
			pre.push_back((P) { h, sum });
		} else {
			dfs(now + 1, end, type, h, sum);
			if(p[now].h >= h) dfs(now + 1, end, type, p[now].h, sum + p[now].g);
		}
	} else {
		if(now > end) {
			sub.push_back((P) { ext, sum });
		} else {
			dfs(now + 1, end, type, h, sum, ext);
			if(p[now].h >= h) dfs(now + 1, end, type, p[now].h, sum + p[now].g, ext == 0 ? p[now].h : ext);
		}
	}
}

ll ans;

void sol() {
	dfs(1, n / 2, 1, 0, 0);
	dfs(n / 2 + 1, n, 2, 0, 0);
	for(P t: pre) {
		if(t.g >= k) ++ ans;
		tl[hsh[t.h]].push_back(t.g);
	}
	
	for(int i = 1 ; i <= cnt ; ++ i) {
		if(tl[i].size()) sort(tl[i].begin(), tl[i].end());
	}
	
	for(P t: sub) {
		ll hr = t.h, sr = t.g;
		if(sr >= k) ++ ans;
		for(ll HL: h) {
			if(HL > hr) break;
			ll hl = hsh[HL];
			if(tl[hl].back() >= k - sr) {
				ans += tl[hl].size() - (lower_bound(tl[hl].begin(), tl[hl].end(), k - sr) - tl[hl].begin());
			}
		}
	}
	
	cout << ans;
}

int main() {
	freopen("san.in", "r", stdin);
	freopen("san.out", "w", stdout);
	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) cin >> p[i].h >> p[i].g;
	for(int i = 1 ; i <= n / 2 ; ++ i) h.push_back(p[i].h);
	sort(h.begin(), h.end());
	h.erase(unique(h.begin(), h.end()), h.end());
	for(ll x: h) hsh[x] = ++ cnt;
	if(n == 1) cout << (p[1].g >= k) << endl;
	else sol();
}
