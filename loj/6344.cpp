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

const int lim = 1e7;

ll n, ans;

#define ll __int128
inline ll sub_f(ll a, ll b, ll c, ll n) {
    if(n <= 0) return 0;
    return
        n * (n - 1) / 2 * (a / c)
      + n * (b / c)
      + sub_f(c, (a * n + b) % c, a % c, (a % c * n + b % c) / c);
}
inline ll f(ll a, ll b, ll c, ll n) {
    if(c < 0) {
        c = -c;
        a = -a, b = -b;
        return f(a, b, c, n);
    }
    if(a < 0) {
        a = -a;
        return f(a, b - a * (n - 1), c, n);
    }
    if(b < 0) {
        b = -b;
        ll k = b / c + (b % c != 0);
        return f(a, k * c - b, c, n) - k * n;
    }
    return sub_f(a, b, c, n);
}
#undef ll

inline ll sol(ll bit) {
    ll res = 0;
    for(ll i = lim + 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        ll k = n / i;
        res += f(-k, n, 1ll << bit, j + 1) - f(-k, n, 1ll << bit, i);
        res &= 1;
    }
    return res;
}

int main() {
    scanf("%lld", &n);
    for(ll bit = 0 ; bit < 41 ; ++ bit) {
        ans |= sol(bit) << bit;
    }
    for(ll i = min(n, (ll) lim) ; i ; -- i) {
        ans ^= n % i;
    }
    printf("%lld\n", ans);
}
