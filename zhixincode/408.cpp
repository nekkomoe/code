#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

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

const int N = 1e5 + 10, mod = 998244353;

struct Mat {
    ll a[3][3];
    Mat() { memset(a, 0, sizeof a); }
    ll *operator [] (int x) { return a[x]; }
    void output() {
        for(int i = 0 ; i < 3 ; ++ i) {
            for(int j = 0 ; j < 3 ; ++ j) {
                printf("%lld ", a[i][j]);
            }
            puts("");
        }
    }
};
Mat operator * (Mat a, Mat b) {
    Mat c;
    for(int i = 0 ; i < 3 ; ++ i)
        for(int j = 0 ; j < 3 ; ++ j)
            for(int k = 0 ; k < 3 ; ++ k)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j] % mod) % mod;
    return c;
}
Mat pw(Mat a, ll b) {
    Mat res;
    res[0][0] = res[1][1] = res[2][2] = 1;
    for( ; b ; b >>= 1, a = a * a)
        if(b & 1)
            res = res * a;
    return res;
}

Mat init[N];
int n, m;

Mat sum[N * 10];
int vis[N * 10], rat[N * 10], bin[N];
Mat mem[N][25];

#define lc (id << 1)
#define rc (id << 1 | 1)
void push(int id, int l, int r) {
    if(vis[id]) {
        vis[id] = 0, vis[lc] = vis[rc] = 1;
        rat[lc] = rat[rc] = rat[id];
        sum[id] = mem[rat[id]][bin[r - l + 1]];
    }
}
void upd(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
    sum[id] = sum[lc] * sum[rc];
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        sum[id] = init[l];
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        sum[id] = sum[lc] * sum[rc];
    }
}

Mat tmp;
void modify(int id, int l, int r, int ql, int qr, int T) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) {
        vis[id] = 1;
        rat[id] = T;
        return ;
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, T);
    } else if(ql >= mid + 1) {
        modify(rc, mid + 1, r, ql, qr, T);
    } else {
        modify(lc, l, mid, ql, mid, T), modify(rc, mid + 1, r, mid + 1, qr, T);
    }
    upd(id, l, r);
}

void ask(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) {
        tmp = tmp * sum[id];
    } else if(qr <= mid) {
        ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        ask(rc, mid + 1, r, ql, qr);
    } else {
        ask(lc, l, mid, ql, mid);
        ask(rc, mid + 1, r, mid + 1, qr);
    }
}

int len;

int main() {
    n = io(), m = io();
    -- n;
    for(int T = 1 ; T <= n ; ++ T) {
        for(int i = 0 ; i < 3 ; ++ i) {
            for(int j = 0 ; j < 3 ; ++ j) {
                init[T][i][j] = io();
            }
        }
    }
    len = 1;
    while(len <= n) len <<= 1;
    n = len;
    for(int i = 1 ; (1 << i) <= n ; ++ i) bin[1 << i] = i;
    build(1, 1, n);
    for(int T = 1 ; T <= m ; ++ T) {
        int op = io(), l = io(), r = io();
        if(op == 1) {
            for(int i = 0 ; i < 3 ; ++ i) {
                for(int j = 0 ; j < 3 ; ++ j) {
                    mem[T][0][i][j] = io();
                }
            }
            for(int i = 1 ; i <= 20 ; ++ i) {
                mem[T][i] = mem[T][i - 1] * mem[T][i - 1];
            }
            modify(1, 1, n, l, r, T);
        } else {
            for(int i = 0 ; i < 3 ; ++ i) for(int j = 0 ; j < 3 ; ++ j) tmp[i][j] = i == 0;
            ask(1, 1, n, l, r - 1);
            ll ans = (tmp[0][0] + tmp[0][1] + tmp[0][2]) % mod;
            if(ans < 0) ans += mod;
            io(ans);
        }
    }
}
