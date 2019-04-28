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


const int N = 6e5 + 10;

int n, mod, m, t, bin[25], b[25][25], cnt1[N], cnt2[N], inv3;

inline ll getphi(ll n) {
    ll res = n;
    for(ll i = 2 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            res -= res / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) {
        res -= res / n;
    }
    return res;
}

inline ll pw(ll a, int b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

inline ll inc(ll a, ll b) {
    return a + b >= mod ? a + b - mod : a + b;
}

inline ll dec(ll a, ll b) {
    return a - b < 0 ? a - b + mod : a - b;
}

struct ZW {
    int a, b; // a + b * w
    inline ZW operator + (ZW t) {
        return (ZW) { inc(a, t.a), inc(b, t.b) };
    }
    inline ZW operator - (ZW t) {
        return (ZW) { dec(a, t.a), dec(b, t.b) };
    }
    inline ZW operator * (ZW t) {
        return (ZW) { dec((ll) a * t.a % mod, (ll) b * t.b % mod), dec(inc((ll) b * t.a % mod, (ll) a * t.b % mod), (ll) b * t.b % mod) };
    }
    inline ZW operator * (ll t) {
        return (ZW) { (ll) a * t % mod, (ll) b * t % mod };
    }
    inline ZW wn(int t) {
        if(t == 1) {
            return (ZW) { dec(0, b), dec(a, b) };
        } else {
            return (ZW) { dec(b, a), dec(0, a) };
        }
    }
} f[N], B[N], nek[3];

inline ZW pw(ZW a, int b) {
    ZW res = (ZW) { 1, 0 };
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            res = res * a;
        }
    }
    return res;
}

void fwt(ZW *f, int ty) {
    for(int i = 1 ; i < n ; i *= 3) {
        for(int j = 0, len = i * 3 ; j < n ; j += len) {
            for(int k = 0 ; k < i ; ++ k) {
                nek[0] = f[j + k];
                nek[1] = f[j + i + k];
                nek[2] = f[j + (i << 1) + k];
                f[j + k] = nek[0] + nek[1] + nek[2];
                f[j + i + k] = nek[0] + nek[1].wn(1) + nek[2].wn(2);
                f[j + (i << 1) + k] = nek[0] + nek[1].wn(2) + nek[2].wn(1);
                if(ty) {
                    swap(f[j + i + k], f[j + (i << 1) + k]);
                    f[j + k] = f[j + k] * inv3;
                    f[j + i + k] = f[j + i + k] * inv3;
                    f[j + (i << 1) + k] = f[j + (i << 1) + k] * inv3;
                }
            }
        }
    }
}

int main() {
    m = io(), t = io(), mod = io();
    n = pow(3, m);
    for(int i = 0 ; i < n ; ++ i) {
        f[i].a = io();
    }
    for(int i = 0 ; i <= m ; ++ i) {
        for(int j = 0 ; j <= m - i ; ++ j) {
            b[i][j] = io();
        }
    }

    if(mod == 1) {
        for(int i = 0 ; i < n ; ++ i) {
            io(0);
        }
        return 0;
    }

    inv3 = pw(3, getphi(mod) - 1);

    bin[0] = 1;
    for(int i = 1 ; i < 20 ; ++ i) {
        bin[i] = bin[i - 1] * 3;
    }

    for(int i = 0 ; i < n ; ++ i) {
        cnt1[i] = cnt1[i / 3] + (i % 3 == 1);
        cnt2[i] = cnt2[i / 3] + (i % 3 == 2);
    }

    for(int i = 0 ; i < n ; ++ i) {
        B[i].a = b[cnt1[i]][cnt2[i]];
    }

    fwt(f, 0), fwt(B, 0);

    for(int i = 0 ; i < n ; ++ i) {
        f[i] = f[i] * pw(B[i], t);
    }

    fwt(f, 1);

    for(int i = 0 ; i < n ; ++ i) {
        io(f[i].a);
    }
}
