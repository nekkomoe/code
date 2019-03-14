#pragma GCC optimize(2)
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




const int N = 1e6 + 10, mod = 99991;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, k, a[N];

ll neko[N];
#define double long double
const double pi = acos(-1);
// typedef complex<double> cp;
struct cp {
    double x, y;
    cp(double x = 0, double y = 0) : x(x), y(y) {}
    double real() { return x; }
    cp operator + (cp t) {
        return cp(x + t.x, y + t.y);
    }
    cp operator - (cp t) {
        return cp(x - t.x, y - t.y);
    }
    cp operator * (cp t) {
        return cp(x * t.x - y * t.y, x * t.y + y * t.x);
    }
    cp operator / (double t) {
        return cp(x / t, y);
    }
};


cp A[N], B[N], f[N];
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}




map<int, int> tra; int tot;
vector<cp> wn_init[30][2];
vector<int> rev_init[30];

int get(int n) {
    if(tra.count(n)) return tra[n];
    int id = tra[n] = tot ++;

    vector<int> rev_res(n);
    for(int i = 0 ; i < n ; ++ i) rev_res[i] = rev(i, n);
    rev_init[id] = rev_res;

    vector<cp> wn_res(n + 1);

    for(int i = 2 ; i <= n ; i <<= 1) {
        wn_res[i] = cp(cos(2 * pi * -1 / i), sin(2 * pi * -1 / i));
    }
    wn_init[id][0] = wn_res;

    for(int i = 2 ; i <= n ; i <<= 1) {
        wn_res[i] = cp(cos(2 * pi * 1 / i), sin(2 * pi * 1 / i));
    }
    wn_init[id][1] = wn_res;

    return id;
}





void fft(cp *a, int ty, int n) {
    int p = get(n);
    // for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];
    for(int i = 0 ; i < n ; ++ i) f[rev_init[p][i]] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        // cp wn = cp(cos(2 * pi * ty / i), sin(2 * pi * ty / i));
        cp wn = wn_init[p][ty == 1][i];
        for(int j = 0 ; j < n ; j += i) {
            cp w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                cp u = f[k], v = f[k + i / 2] * w;
                f[k] = u + v, f[k + i / 2] = u - v;
                w = w * wn; // w *= wn;
            }
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        a[i] = f[i];
        // if(ty == 1) a[i] /= n;
        if(ty == 1) a[i] = a[i] / n;
    }
}

vector<int> mul(vector<int> a, vector<int> b) {
    int reslen = a.size() + b.size();
    vector<int> res;
    int n = 1; while(n <= reslen) n <<= 1;
    for(int i = 0 ; i < n ; ++ i) A[i] = B[i] = 0;
    for(int i = 0 ; i < a.size() ; ++ i) A[i] = a[i];
    for(int i = 0 ; i < b.size() ; ++ i) B[i] = b[i];
    fft(A, -1, n), fft(B, -1, n);
    // for(int i = 0 ; i < n ; ++ i) A[i] *= B[i];
    for(int i = 0 ; i < n ; ++ i) A[i] = A[i] * B[i];
    fft(A, 1, n);
    res.resize(reslen - 1);
    for(int i = 0 ; i < res.size() ; ++ i) res[i] = ll(A[i].real() + 0.5) % mod;
    return res;
}

vector<int> sol(int l, int r) {
    if(l == r) {
        vector<int> res;
        res.resize(2);
        res[0] = 1;
        res[1] = neko[l];
        return res;
    } else {
        int mid = (l + r) >> 1;
        return mul(sol(l, mid), sol(mid + 1, r));
    }
}

ll runprog(ll p) {
    for(int i = 1 ; i <= n ; ++ i) neko[i] = pw(p, a[i]) % mod;
    return sol(1, n)[k];
}

int main() {
    n = io(), k = io();
    if(k > n) return io(0), 0;
    for(int i = 1 ; i <= n ; ++ i) a[i] = io();
    ll f0 = io(), f1 = io();

    ll A = (f0 + f1) * pw(4, mod - 2) % mod;
    ll B = (3 * f0 - f1) * pw(4, mod - 2) % mod;
    ll ans = 0;

    ans = (ans + A * runprog(3) % mod) % mod;
    ans = (ans + B * runprog(mod - 1) % mod) % mod;

    io(ans < 0 ? ans + mod : ans);
}
