%:pragma GCC optimize(2)
%:pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, K = 11;
int n, k, kh, ks; ll f;
int a[K], hom[K], sch[K];

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
    inline ll xuint() {
        int c = xchar();
		ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

template<typename T> inline void read(T &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

inline ll getdis(int *b) {
	ll r = 0;
	for(int i = 1 ; i <= k ; ++ i) r += (ll) (a[i] - b[i]) * (a[i] - b[i]);
	return r;
}

int pos[N], bit[N];
inline void add(int x, int y) { for( ; x <= n ; x += x & -x) bit[x] += y; }
inline int query(int x) { int r = 0; for( ; x ; x -= x & -x) r += bit[x]; return r; }

struct T { int id; ll val; } da[N], db[N];
bool operator < (T a, T b) { return a.val < b.val; }

int main() {
//	read(n), read(k), read(f), read(kh), read(ks);
	n = io.xuint(), k = io.xuint(), f = io.xuint(), kh = io.xuint(), ks = io.xuint();
	for(int i = 1 ; i <= k ; ++ i) {
//		read(hom[i]);
		hom[i] = io.xuint();
	}
	for(int i = 1 ; i <= k ; ++ i) {
//		read(sch[i]);
		sch[i] = io.xuint();
	}
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= k ; ++ j) {
			a[j] = io.xuint();
//			read(a[j]);
		}
		da[i] = (T) { i, getdis(hom) }, db[i] = (T) { i, getdis(sch) };
	}
	
	sort(da + 1, da + 1 + n), sort(db + 1, db + 1 + n);
	
	for(int i = 1 ; i <= n ; ++ i) pos[da[i].id] = i;	
	for(int i = 1 ; i <= n ; ++ i) add(pos[db[i].id], 1);
	
	int ans = 0;
	
	for(int i = n ; i ; -- i) {
		if(kh * da[i].val <= f || ks * db[i].val <= f) {
			ans = i;
			break;
		}
	}
	for(int i = 1, j = n ; i <= n ; ++ i) {
		if(i + 1 <= n && da[i].val == da[i + 1].val) continue;
		if(kh * da[i].val > f) break;
		ll dkb = f - kh * da[i].val;
		while(j - 1 >= 1 && ks * db[j].val > dkb) add(pos[db[j --].id], -1);
		if(ks * db[j].val > dkb) break;
		ans = max(ans, i + j - query(i));
	}
	printf("%d\n", ans);
}
