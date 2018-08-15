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
const int N = 1e6 + 10, base = 137, p = 998244353;
typedef long long ll;
int n, m, q;
char s[N], t[N];
ll f[N], g[N], pp[N], ps[N], qp[N], qs[N], pw[N];

void calc(char *s, ll *f, ll *pre, ll *sub, int n) {
	for(int i = 1 ; i <= n ; ++ i) pre[i] = (pre[i - 1] * base + s[i]) % p;
	
	for(int i = n ; i >= 1 ; -- i) sub[i] = (sub[i + 1] * base + s[i]) % p;
	
	// 1
	for(int i = 1 ; i <= n ; ++ i) {
		int l = 0, r = min(i - 1, n - i), len = 0;
		while(l <= r) {
			int mid = (l + r) >> 1;
			// [i - mid .. i] [i .. i + len]
			ll x = (pre[i] - pre[i - mid - 1] * pw[mid + 1] % p) % p;
			ll y = (sub[i] - sub[i + mid + 1] * pw[mid + 1] % p) % p;
			x = (x + p) % p;
			y = (y + p) % p;
			if(x == y) len = mid, l = mid + 1;
			else r = mid - 1;
		}
		// [i - len .. i] [i .. i + len]
		f[i - len] ++;
		f[i + 1] --;
	}
	
	// 2
	for(int i = 1 ; i < n ; ++ i) {
		if(s[i] != s[i + 1]) continue;
		int l = 0, r = min(i - 1, n - i - 1), len = 0;
		while(l <= r) {
			int mid = (l + r) >> 1;
			ll x = (pre[i] - pre[i - mid - 1] * pw[mid + 1] % p) % p;
			ll y = (sub[i + 1] - sub[i + 1 + mid + 1] * pw[mid + 1] % p) % p;
			x = (x + p) % p;
			y = (y + p) % p;
			if(x == y) len = mid, l = mid + 1;
			else r = mid - 1;
		}
		// [i - len, i] [i + 1, i + 1 + len]
		f[i - len] ++;
		f[i + 1] --;
	}
	for(int i = 1 ; i <= n ; ++ i) f[i] += f[i - 1];
	for(int i = 1 ; i <= n ; ++ i) f[i] += f[i - 1];
	f[n + 1] = f[n];
}

ll sol(int x, int y) {
	if(s[x] != t[y]) return 0;
	int l = 0, r = min(n - x, m - y), len = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		ll a = (ps[x] - ps[x + mid + 1] * pw[mid + 1] % p) % p;
		ll b = (qs[y] - qs[y + mid + 1] * pw[mid + 1] % p) % p;
		a = (a + p) % p;
		b = (b + p) % p;
		if(a == b) len = mid, l = mid + 1;
		else r = mid - 1;
	}
	return f[x + len + 1] - f[x] + g[y + len + 1] - g[y] + len + 1;
}

int main() {
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
	scanf("%*s");
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	reverse(t + 1, t + 1 + m);
	for(int i = pw[0] = 1 ; i <= max(n, m) ; ++ i) pw[i] = pw[i - 1] * base % p;
	calc(s, f, pp, ps, n);
	calc(t, g, qp, qs, m);
	scanf("%d", &q);
	for(int i = 1, x, y ; i <= q ; ++ i) {
		scanf("%d%d", &x, &y);
		printf("%lld\n", sol(x, y));
	}
}
