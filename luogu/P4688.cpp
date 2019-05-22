// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int QBLO = 25000;
const int N = 1e5 + 10;

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
        // if (pos == len) exit(0);
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

int bel[N], a[N], n, m;

struct NEKQ {
    int l1, r1, l2, r2, l3, r3;
} nekq[N];

int cnt[N];
ll ans[N];

bitset<100010> f[QBLO], cur;

inline void chn(int val, int tag) {
    val = a[val];
    if(tag < 0) {
        cur[val + cnt[val] - 1] = 0;
    } else {
        cur[val + cnt[val]] = 1;
    }
    cnt[val] += tag;
}

struct Q {
    int l, r, id, bel;
} ak[N * 3];
inline bool cmp(Q a, Q b) {
    return a.bel == b.bel ? a.r < b.r : a.bel < b.bel;
}
int vis[N];

inline void runprog(int ql, int qr) {
    memset(cnt, 0, sizeof cnt);
    cur = 0;
    int tot = 0;
    for(int i = ql ; i <= qr ; ++ i) {
        ak[tot ++] = (Q) { nekq[i].l1, nekq[i].r1, i, bel[nekq[i].l1] };
        ak[tot ++] = (Q) { nekq[i].l2, nekq[i].r2, i, bel[nekq[i].l2] };
        ak[tot ++] = (Q) { nekq[i].l3, nekq[i].r3, i, bel[nekq[i].l3] };
        vis[i - ql + 1] = 0;
    }
    sort(ak, ak + tot, cmp);
    int l = ak[0].l, r = ak[0].r;
    for(int i = l ; i <= r ; ++ i) {
        chn(i, 1);
    }
    for(int i = 0 ; i < tot ; ++ i) {
        int nl = ak[i].l, nr = ak[i].r;
        while(r < nr) chn(++ r, 1);
        while(l > nl) chn(-- l, 1);
        while(r > nr) chn(r --, -1);
        while(l < nl) chn(l ++, -1);
        int id = ak[i].id - ql + 1;
        if(!vis[id]) {
            vis[id] = 1;
            f[id] = cur;
        } else {
            f[id] &= cur;
        }
    }
    for(int i = ql ; i <= qr ; ++ i) {
        ans[i] -= f[i - ql + 1].count() * 3;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    vector<int> num;
    for(int i = 1, ble = int(sqrt(n) + 1) ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        num.push_back(a[i]);
        bel[i] = (i - 1) / ble + 1;
    }
    sort(num.begin(), num.end());
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        nekq[i].l1 = io(), nekq[i].r1 = io(),
        nekq[i].l2 = io(), nekq[i].r2 = io(),
        nekq[i].l3 = io(), nekq[i].r3 = io();
        ans[i] += nekq[i].r1 - nekq[i].l1 + 1;
        ans[i] += nekq[i].r2 - nekq[i].l2 + 1;
        ans[i] += nekq[i].r3 - nekq[i].l3 + 1;
    }
    const int TB = QBLO - 10;
    for(int i = 1 ; i <= m ; i += TB) {
        runprog(i, min(m, i + TB - 1));
    }
    for(int i = 1 ; i <= m ; ++ i) {
        io(ans[i]);
    }
}
