#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
const int N = 5e4 + 10;
int n, m, a[N];
int bel[N], len, L[N], R[N], cnt, ql, qr;
int mle[N][230], wa[N];
   
struct FastIO {
    static const int S = 2e7;
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
        int t; scanf("%d", &t);
        return t;
           
        int c = xchar(), x = 0, flag = 0;
        while (c <= 32) flag |= c == '-', c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return flag ? -x : x;
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
   
int getle(int l, int r, int x) {
    int res = 0;
    if(bel[l] == bel[r]) {
        for(int i = l ; i <= r ; ++ i) {
            res += a[i] <= x;
        }
    } else {
        for(int i = l ; i <= R[bel[l]] ; ++ i) {
            res += a[i] <= x;
        }
        for(int i = bel[l] + 1 ; i <= bel[r] - 1 ; ++ i) {
            res += upper_bound(mle[i] + 1, mle[i] + 1 + wa[i], x) - mle[i] - 1;
        }
        for(int i = L[bel[r]] ; i <= r ; ++ i) {
            res += a[i] <= x;
        }
    }
    return res;
}
   
int getrank(int l, int r, int x) {
    return getle(l, r, x - 1) + 1;
}
   
int getkth(int l, int r, int k) {
       
    int x = ql, y = qr, ans = -1;
       
    while(x <= y) {
        int mid = (x + y) >> 1;
        int rk = getrank(l, r, mid);
        if(rk <= k) {
            ans = mid;
            x = mid + 1;
        } else {
            y = mid - 1;
        }
    }
    return ans;
}
   
void modify(int pos, int x) {
    a[pos] = x; int id = bel[pos];
    wa[id] = 0;
    for(int i = L[id] ; i <= R[id] ; ++ i) {
        mle[id][++ wa[id]] = a[i];
    }
    sort(mle[id] + 1, mle[id] + 1 + wa[id]);
    ql = min(ql, x), qr = max(qr, x);
}
   
void sol() {
    int op, l, r, x, k, pos;
    op = io();
    if(op == 1) {
        l = io(), r = io(), x = io();
        io(getrank(l, r, x));
    } else if(op == 2) {
        l = io(), r = io(), k = io();
        io(getkth(l, r, k));
    } else if(op == 3) {
        pos = io(), x = io();
        modify(pos, x);
    } else if(op == 4) {
        l = io(), r = io(), x = io();
        io(getkth(l, r, getle(l, r, x - 1)));
    } else if(op == 5) {
        l = io(), r = io(), x = io();
        io(getkth(l, r, getle(l, r, x) + 1));
    }
}
   
int main() {
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    n = io(), m = io();
    int len = min(n, (int) sqrt(n) + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = io();
        bel[i] = (i - 1) / len + 1;
        R[bel[i]] = i;
        if(!L[bel[i]]) L[bel[i]] = i;
        mle[bel[i]][++ wa[bel[i]]] = a[i];
        cnt = bel[i];
    }
    ql = qr = a[1];
    for(int i = 1 ; i <= n ; ++ i) ql = min(ql, a[i]), qr = max(qr, a[i]);
    for(int i = 1 ; i <= cnt ; ++ i) {
        sort(mle[i] + 1, mle[i] + 1 + wa[i]);
    }
    while(m --) sol();
}
