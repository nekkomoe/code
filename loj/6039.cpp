#include "bits/stdc++.h"
typedef long long ll;
using namespace std;

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
        wchar(' ');
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

const int N = 1e6 + 10, K = 5e4 + 10, C = 310;

int n, k, lim, p;
vector<int> g[C];

ll f[2][K], cost[N], val[N];

int siz;

ll lastf[N], newf[N];

void sol(int ql, int qr, int l, int r) {
    // 查询区间 [ql, qr]
    // 决策点 [l, r]
    int mid = (ql + qr) >> 1, pos = l;
    for(int i = max(l, mid - siz) ; i <= min(mid, r) ; ++ i) {
        // 查询大小不爆炸
        ll newval = lastf[i] + val[mid - i];
        if(newf[mid] < newval) {
            pos = i;
            newf[mid] = newval;
        }
    }
    if(ql < mid) sol(ql, mid - 1, l, pos);
    if(mid < qr) sol(mid + 1, qr, pos, r);
}

int main() {
    n = io(), k = io();
    for(int i = 1 ; i <= n ; ++ i) {
        int c = io(), v = io();
        g[c].push_back(v);
        lim = max(lim, c);
    }
    for(int i = 1 ; i <= lim ; ++ i) {
        sort(g[i].begin(), g[i].end(), greater<int> ());
    }

    for(int c = 1 ; c <= lim ; ++ c) {

        if(g[c].empty()) continue;

        p ^= 1;

        siz = 0;
        for(int j = 0 ; j < g[c].size() ; ++ j) {
            ++ siz;
            cost[siz] = cost[siz - 1] + c;
            val[siz] = val[siz - 1] + g[c][j];
        }

        for(int k = 1 ; k <= :: k ; ++ k) f[p][k] = 0;

        for(int i = 0 ; i < c ; ++ i) {
            // mod c = i
            int top = 0;
            for(int j = 0 ; j * c + i <= k ; ++ j) {
                lastf[j] = f[!p][j * c + i];
                newf[j] = 0;
                top = j;
            }
            top = (k - i) / c;
            
            sol(0, top, 0, top);
            
            for(int j = 0 ; j * c + i <= k ; ++ j) {
                f[p][j * c + i] = max(f[p][j * c + i], newf[j]);
            }
        }

        for(int k = 0 ; k <= :: k ; ++ k) {
            f[p][k] = max(f[p][k], f[!p][k]);
            // if(k - 1 >= 0) f[p][k] = max(f[p][k], f[p][k - 1]);
        }

    }
    for(int i = 1 ; i <= k ; ++ i) {
        io(f[p][i]);
        // if(i == 2) break;
    }
}
