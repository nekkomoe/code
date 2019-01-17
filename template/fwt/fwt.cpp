#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1 << 20, mod = 998244353;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2);

int n; ll a[N], b[N];

namespace OR {

ll a[N], b[N];

void fwt(ll *f, int n, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j + i / 2 < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) f[k] = u, f[k + i / 2] = (u + v) % mod;
                else f[k] = u, f[k + i / 2] = (v - u) % mod;
            }
        }
    }
}

void sol(int n, ll *A, ll *B) {
    for(int i = 0 ; i < n ; ++ i) a[i] = A[i], b[i] = B[i];
    fwt(a, n, 0), fwt(b, n, 0);
    for(int i = 0 ; i < n ; ++ i) a[i] = a[i] * b[i] % mod;
    fwt(a, n, 1);
    for(int i = 0 ; i < n ; ++ i) printf("%lld ", (a[i] % mod + mod) % mod);
    puts("");
}
}

namespace AND {

ll a[N], b[N];

void fwt(ll *f, int n, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j + i / 2 < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) f[k] = (u + v) % mod, f[k + i / 2] = v;
                else f[k] = (u - v) % mod, f[k + i / 2] = v;
            }
        }
    }
}

void sol(int n, ll *A, ll *B) {
    for(int i = 0 ; i < n ; ++ i) a[i] = A[i], b[i] = B[i];
    fwt(a, n, 0), fwt(b, n, 0);
    for(int i = 0 ; i < n ; ++ i) a[i] = a[i] * b[i] % mod;
    fwt(a, n, 1);
    for(int i = 0 ; i < n ; ++ i) printf("%lld ", (a[i] % mod + mod) % mod);
    puts("");
}
}

namespace XOR {

ll a[N], b[N];

void fwt(ll *f, int n, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j + i / 2 < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) f[k] = (u + v) % mod, f[k + i / 2] = (u - v) % mod;
                else f[k] = (u + v) * inv2 % mod, f[k + i / 2] = (u - v) * inv2 % mod;
            }
        }
    }
}

void sol(int n, ll *A, ll *B) {
    for(int i = 0 ; i < n ; ++ i) a[i] = A[i], b[i] = B[i];
    fwt(a, n, 0), fwt(b, n, 0);
    for(int i = 0 ; i < n ; ++ i) a[i] = a[i] * b[i] % mod;
    fwt(a, n, 1);
    for(int i = 0 ; i < n ; ++ i) printf("%lld ", (a[i] % mod + mod) % mod);
    puts("");
}

}

int main() {
    scanf("%d", &n), n = 1 << n;
    for(int i = 0 ; i < n ; ++ i) scanf("%lld", &a[i]);
    for(int i = 0 ; i < n ; ++ i) scanf("%lld", &b[i]);
    OR :: sol(n, a, b);
    AND :: sol(n, a, b);
    XOR :: sol(n, a, b);
}
