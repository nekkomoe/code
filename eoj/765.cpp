#pragma GCC optimize(2)
// #pragma GCC optimize(3)
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

const int N = 81, mod = 998244353;
int f[N][N][N * N / 2], g[N][N * N / 2];
vector<int> to[N];
int sz[N], n;

inline int pw(register int a, register int b) {
    register int r = 1;
    for( ; b ; b >>= 1, a = (ll) a * a % mod) {
        if(b & 1) {
            r = (ll) r * a % mod;
        }
    }
    return r;
}

#define calc(n) (((n) * ((n) + 1)) >> 1)

inline void dfs(int u, int fa) {
    f[u][1][1] = sz[u] = 1;
    f[u][0][0] = -1;
    for(int v: to[u]) {
        if(v == fa) continue;
        dfs(v, u);
        for(register int i = sz[u] + sz[v] ; i >= 0 ; -- i) {
            for(register int j = calc(sz[u] + sz[v]) ; j >= 0 ; -- j) {
                g[i][j] = 0;
            }
        }
        for(register int i = 0 ; i <= sz[u] ; ++ i) {
            for(register int k = calc(sz[u]) ; k >= 0 ; -- k) {
                if(f[u][i][k]) {
                    for(register int j = 0 ; j <= sz[v] ; ++ j) {
                        for(register int l = calc(sz[v]) ; l >= 0 ; -- l) {
                            if(f[v][j][l]) {
                                (g[i ? i + j : 0][k + l + i * j] += (ll) f[u][i][k] * f[v][j][l] % mod) %= mod;
                            }
                        }
                    }
                }
            }
        }
        sz[u] += sz[v];
        for(register int i = 0 ; i <= sz[u] ; ++ i) {
            for(register int j = calc(sz[u]) ; j >= 0 ; -- j) {
                f[u][i][j] = g[i][j];
            }
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
//    freopen("jiandanti.in", "r", stdin);
//    freopen("jiandanti.out", "w", stdout);
#endif
    n = io();
    for(register int i = 1, u, v ; i < n ; ++ i) {
        u = io(), v = io();
        to[u].push_back(v);
        to[v].push_back(u);
    }
    dfs(1, 0);
    ll ans = 0;
    for(register int j = calc(n) ; j >= 0 ; -- j) {
        register ll cnt = 0;
        for(register int i = 0 ; i <= n ; ++ i) {
            (cnt += f[1][i][j]) %= mod;
        }
        if(cnt) {
            ll coef = pw(1 - (ll) j * pw(calc(n), mod - 2) % mod, mod - 2);
            ans -= cnt * coef % mod;
            ans %= mod;
        }
    }
    if(ans < 0) ans += mod;
    io(ans);
}
