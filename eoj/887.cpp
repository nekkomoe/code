#include <bits/stdc++.h>
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
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline ll operator ! () {
        int c = xchar(), f = 0; ll x = 0;
        while(!isdigit(c)) {
            f |= c == '-';
            c = xchar();
        }
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return f ? -x : x;
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

const int N = 2e6 + 10, mod = 1e9 + 7;

int n;
struct P {
    ll x, y;
} p[N];
P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}
ll s[N], tbS;
ll ans;
ll ss[N];

void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

ll calcArea(int i, int j) {
    // i -> j 的下半截的面积
    return s[j] - s[i] - (p[i] - p[j]) * (p[0] - p[j]);
}

ll X0, Y0, x[N], y[N];
ll sx[N], sy[N];

ll calcArea_presum(int i, int j) {
    ll res = 0;

    if(i + 2 <= j) {
        upd(res, (ss[j] - ss[i + 1]) % mod);
        upd(res, -s[i] % mod * (j - i - 1) % mod);

        ll x1 = x[i], y1 = y[i], tmp = 0;
        upd(tmp, (x1 * Y0 % mod - X0 * y1 % mod) * (j - i - 1) % mod);
        upd(tmp, (sx[j] - sx[i + 1]) * (y1 - Y0) % mod);
        upd(tmp, (sy[j] - sy[i + 1]) * (X0 - x1) % mod);

        upd(res, -tmp);
    }

    return res;
}

ll calcArea_up(int i, int j) {
    // i -> j 的上半截的面积
    return tbS - calcArea(i, j);
}
ll calcArea_sufsum_up(int i, int j) {
    ll res = 0;
    int lim = (i == 0 ? n - 1 : n) - 1;
    if(j <= lim) {
        upd(res, tbS % mod * (lim - j + 1) % mod);
        ll tmp = calcArea_presum(i, lim) - calcArea_presum(i, j - 1);
        upd(res, -tmp);
    }
    return res;
}

void n2000() {
    for(int i = 0 ; i < n ; ++ i) {
        for(int j = i + 2 ; j < n && (j + 1) % n != i ; ++ j) {
            ll A = calcArea(i, j);
            upd(ans, abs(A - (tbS - A)) % mod);
        }
    }
}

void n_ano() {
    // 答案= (面积>S/2) - (面积<S/2)
    for(int i = 0 ; i < n ; ++ i) {
        int L = i + 2, R = (i == 0 ? n - 2 : n - 1);
        if(L > R) continue;
        int l, r, t;
        
        // 先把 area < S / 2 的搞出来，下侧，也就是 < S / 2 最大的
        l = L, r = R, t = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if((__int128) calcArea(i, mid) * 2 < tbS) {
                t = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        // printf("down: %d -> %d\n", i, t);

        if(t != -1) {
            // 计算 < S / 2 的贡献
            upd(ans, -(calcArea_presum(i, t)));

            // 计算 > S / 2 的贡献
            while(t + 1 <= R && calcArea(i, t + 1) * 2 == tbS) ++ t;
            upd(ans, (calcArea_presum(i, R) - calcArea_presum(i, t)) % mod);
        } else {
            // 计算 > S / 2 的贡献
            t = L;
            if(calcArea(i, t) * 2 == tbS) {
                while(t + 1 <= R && calcArea(i, t + 1) * 2 == tbS) ++ t;
                upd(ans, (calcArea_presum(i, R) - calcArea_presum(i, t)) % mod);
            } else {
                upd(ans, calcArea_presum(i, R));
            }
        }

        // 然后计算 area < S / 2，上侧，也就是 < S / 2 最小的
        l = L, r = R, t = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if((__int128) calcArea_up(i, mid) * 2 < tbS) {
                t = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        if(t != -1) {
            // 计算 < S / 2 的贡献
            upd(ans, -calcArea_sufsum_up(i, t));

            // 计算 > S / 2 的贡献

            while(t - 1 >= L && calcArea_up(i, t - 1) * 2 == tbS) -- t;

            upd(ans, (calcArea_sufsum_up(i, L) - calcArea_sufsum_up(i, t)) % mod);
        } else {
            // 计算 > S / 2 的贡献
            t = R;
            if((__int128) calcArea_up(i, t) * 2 == tbS) {
                while(t - 1 >= L && calcArea_up(i, t - 1) * 2 == tbS) -- t;
                upd(ans, (calcArea_sufsum_up(i, L) - calcArea_sufsum_up(i, t)) % mod);
            } else {
                upd(ans, calcArea_sufsum_up(i, L));
            }
        }
    }
}

int main() {

    // freopen("convex.in", "r", stdin);
    // freopen("convex.out", "w", stdout);

    n = !io;
    for(int i = 0 ; i < n ; ++ i) {
        p[i].x = !io, p[i].y = !io;

        sx[i] = x[i] = p[i].x % mod, sy[i] = y[i] = p[i].y % mod;
        if(i) {
            upd(sx[i], sx[i - 1]);
            upd(sy[i], sy[i - 1]);
        }
    }
    X0 = p[0].x % mod, Y0 = p[0].y % mod;
    for(int i = 0 ; i < n ; ++ i) {
        tbS += p[i] * p[(i + 1) % n];
    }
    tbS = abs(tbS);
    for(int i = 2 ; i < n ; ++ i) {
        s[i] = s[i - 1] + abs((p[i - 1] - p[i]) * (p[0] - p[i]));
        ss[i] = (ss[i - 1] + (s[i] % mod)) % mod;
    }

    if(n <= 2000) {
        n2000();
    } else {
        n_ano();
    }
    
    io((ans % mod + mod) % mod);
}
