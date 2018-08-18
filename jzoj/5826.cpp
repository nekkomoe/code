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
const int N = 30000 + 10, mod = 998244353;
int n, m, q, len, a[N];
char s[N];

struct Mat {
	int a[22][22];
	Mat() { for(int i = 0 ; i < len ; ++ i) for(int j = 0 ; j < len ; ++ j) a[i][j] = 0; }
	int* operator [] (int x) { return a[x]; }
	Mat operator * (Mat b) {
		Mat c;
		for(int i = 0 ; i < len ; ++ i)
			for(int k = 0 ; k < len ; ++ k)
				if(a[i][k])
					for(int j = 0 ; j < len ; ++ j)
						c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
//		for(int i = 0 ; i < len ; ++ i)
//			for(int j = 0 ; j < len ; ++ j)
//				for(int k = 0 ; k < len ; ++ k)
//					c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
		return c;
	}
} mat[N * 4], m0, m1, m01, init;

#define lc (id << 1)
#define rc (id << 1 | 1)

void build(int id, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) {
		if(a[l] == -1) {
			mat[id] = m01;
		} else if(a[l] == 0) {
			mat[id] = m0;
		} else if(a[l] == 1) {
			mat[id] = m1;
		}
	} else {
		build(lc, l, mid), build(rc, mid + 1, r);
		mat[id] = mat[lc] * mat[rc];
	}
}

void modify(int id, int l, int r, int pos, int val) {
	int mid = (l + r) >> 1;
	if(l == r) {
		if(val == -1) {
			mat[id] = m01;
		} else if(val == 0) {
			mat[id] = m0;
		} else if(val == 1) {
			mat[id] = m1;
		}
	} else if(pos <= mid) modify(lc, l, mid, pos, val), mat[id] = mat[lc] * mat[rc];
	else modify(rc, mid + 1, r, pos, val), mat[id] = mat[lc] * mat[rc];
}

Mat query(int id, int l, int r, int ql, int qr) {
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr) return mat[id];
	else if(qr <= mid) return query(lc, l, mid, ql, qr);
	else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
	else return query(lc, l, mid, ql, mid) * query(rc, mid + 1, r, mid + 1, qr);
}

namespace ACM {

	int cnt, nxt[N][2], fail[N], tot[N];
	char s[N];

	void ins() {
		scanf("%s", s);
	    int x = 0;
	    for(int i = 0 ; s[i] ; ++ i) {
	        int c = s[i] - '0';
	        if(!nxt[x][c]) nxt[x][c] = ++ cnt;
	        x = nxt[x][c];
	    }
	    ++ tot[x];
	}

	void bfs() {
		queue<int> q;
	    for(int i = 0 ; i < 2 ; ++ i) {
	        if(nxt[0][i]) {
	            fail[nxt[0][i]] = 0;
	            q.push(nxt[0][i]);
	        }
	    }
	    while(q.size()) {
	        int u = q.front(); q.pop();
	        for(int i = 0 ; i < 2 ; ++ i) {
	            int v = nxt[u][i];
	            if(!v) nxt[u][i] = nxt[fail[u]][i];
	            else {
	                fail[v] = nxt[fail[u]][i];
	                tot[v] |= tot[fail[v]];
	                q.push(v);
	            }
	    	}
	    }
	}
	
	void build() {
		bfs();
		len = cnt + 1;
		for(int i = 0 ; i < len ; ++ i) {
			if(tot[i]) continue;
			m0[i][nxt[i][0]] = 1;
			m1[i][nxt[i][1]] = 1;
			
			
//			m01[i][nxt[i][0]] = m01[i][nxt[i][1]] = 1;
			++ m01[i][nxt[i][0]];
			++ m01[i][nxt[i][1]];
			
//			assert(nxt[i][0] != nxt[i][1]); // ????????????????????
		}
		init[0][0] = 1;
	}
};

int ff_query(int l, int r) {
	long long res = 0;
	Mat mat = init * query(1, 1, n, l, r);
	for(int i = 0 ; i < len ; ++ i)
		if(ACM :: tot[i] == 0)
			res += mat[0][i];
	return res % mod;
}
char op[10];
int main() {
	freopen("kill.in", "r", stdin);
	freopen("kill.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	for(int i = 1 ; i <= m ; ++ i) ACM :: ins(); ACM :: build();
	build(1, 1, n);
	for(int i = 1, x, y ; i <= q ; ++ i) {
		scanf("%s%d%d", op, &x, &y);
		if(op[0] == 'Q') {
			printf("%d\n", ff_query(x, y));
		} else {
			modify(1, 1, n, x, y);
		}
	}
}
