// TLE
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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
using namespace std; typedef long long ll;
const int N = 5e5 + 10, mod = 998244353;

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void space(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

int n, q, ta, tb, A, B, t;

struct Mat {
	int a[3][3];
	Mat() { memset(a, 0, sizeof a); }
	int *operator [] (int x) { return a[x]; }
	Mat operator * (Mat b) {
		Mat c;
		for(int i = 0 ; i < 3 ; ++ i)
			for(int j = 0 ; j < 3 ; ++ j)
				for(int k = 0 ; k < 3 ; ++ k)
					c[i][j] = (c[i][j] + (ll) a[i][k] * b[k][j] % mod) % mod;
		return c;
	}
	void init(int p) {
		int x = ((ll) p * (1 - t) % mod + t) % mod;
		a[0][0] = 1, a[0][1] = 0, a[0][2] = 0;
		a[1][0] = p, a[1][1] = x, a[1][2] = 0;
		a[2][0] = p, a[2][1] = p, a[2][2] = 1;
	}
} mat[N * 4], ini;

Mat pw(Mat a, ll b) {
	Mat r;
	for(int i = 0 ; i < 3 ; ++ i) r[i][i] = 1;
	for( ; b ; b >>= 1, a = a * a)
		if(b & 1)
			r = r * a;
	return r;
}

ll pw(ll a, ll b) {
	ll r = 1;
	for( ; b ; b >>= 1, a = a * a % mod)
		if(b & 1)
			r = r * a % mod;
	return r;
}

int sum[N * 4];

#define lc (id << 1)
#define rc (id << 1 | 1)
void modify(int id, int l, int r, int pos, int val) {
	int mid = (l + r) >> 1;
	if(l == r) {
		mat[id].init(sum[id] = val);
		return ;
	} else if(pos <= mid) {
		modify(lc, l, mid, pos, val);
	} else {
		modify(rc, mid + 1, r, pos, val);
	}
	mat[id] = mat[lc] * mat[rc];
	sum[id] = ((ll) sum[lc] + sum[rc]) % mod;
}

int que;
Mat res;
void ask(int id, int l, int r, int ql, int qr) {
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) {
		que = ((ll) que + sum[id]) % mod;
		res = res * mat[id];
	}
	else if(qr <= mid) return ask(lc, l, mid, ql, qr);
	else if(ql >= mid + 1) return ask(rc, mid + 1, r, ql, qr);
	else ask(lc, l, mid, ql, mid), ask(rc, mid + 1, r, mid + 1, qr);
}

void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) {
		int pa = io(), pb = io();
		mat[id].init(sum[id] = pa * pw(pb, mod - 2) % mod);
	} else {
		build(lc, l, mid), build(rc, mid + 1, r);
		mat[id] = mat[lc] * mat[rc];
		sum[id] = (sum[lc] + sum[rc]) % mod;
	}
}

int main() {
//	freopen("data.in", "r", stdin);
	freopen("omeed.in", "r", stdin);
	freopen("omeed.out", "w", stdout);
io(), n = io(), q = io(); //	scanf("%*d%d%d", &n, &q);
ta = io(), tb = io(); //	scanf("%d%d", &ta, &tb);
A = io(), B = io(); //	scanf("%d%d", &A, &B);
	t = ta * pw(tb, mod - 2) % mod;
	build(1, 1, n);
	ini[0][2] = 1;
	for(int i = 1, op ; i <= q ; ++ i) {
		op = io();
		if(op == 0) {
			int x = io(), wa = io(), wb = io();
			modify(1, 1, n, x, wa * pw(wb, mod - 2) % mod);
		} else {
			int l = io(), r = io(); que = 0; memset(res.a, 0, sizeof res.a); res[0][0] = res[1][1] = res[2][2] = 1;
			ask(1, 1, n, l, r);
			int pe = (ini * res)[0][0];
			ll ans = ((ll) A * que % mod + (ll) B * pe % mod) % mod;
			if(ans < 0) ans += mod;
			io(ans);
		}
	}
}
