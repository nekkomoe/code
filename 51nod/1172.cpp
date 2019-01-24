#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, mod = 1e9 + 7;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int n, k;

ll a[N], b[N], c[N], mem[N], top;

inline void mns(ll *a, ll *b, ll *res, int n) {
    for(int i = 0 ; i < n ; ++ i) res[i] = (a[i] - b[i]) % mod;
}

inline void pls(ll *a, ll *b, ll *c, ll *res, int n) {
    for(int i = 0 ; i < n ; ++ i) res[i] = (a[i] + b[i] + c[i]) % mod;
}

ll *_new(int x) {
    ll *res = mem + top;
    top += x;
    assert(top < N);
    return res;
}
void _delete(int x) {
    top -= x;
}

void sol(ll *a, ll *b, ll *res, int n) {
    if(n == 1) {
        res[0] = a[0] * b[0] % mod;
        res[1] = 0;
    } else if(n > 1) {


        ll *a0b0 = _new(n);
        ll *a1b1 = _new(n); 
        ll *a0a1 = _new(n);
        ll *b1b0 = _new(n);
        ll *a0a1_b1b0 = _new(n); 

        sol(a, b, a0b0, n / 2);
        sol(a + n / 2, b + n / 2, a1b1, n / 2);
        mns(a, a + n / 2, a0a1, n / 2);
        mns(b + n / 2, b, b1b0, n / 2);
        sol(a0a1, b1b0, a0a1_b1b0, n / 2);

        for(int i = 0 ; i < n ; ++ i) {
            res[i] = a0b0[i];
            res[i + n] = a1b1[i];
        }
        pls(a0a1_b1b0, a1b1, a0b0, a0a1_b1b0, n);
        for(int i = 0 ; i < n ; ++ i) {
            (res[i + n / 2] += a0a1_b1b0[i]) %= mod;
        }

        _delete(n);
        _delete(n);
        _delete(n);
        _delete(n);
        _delete(n);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    
    b[0] = 1, b[1] = k;
    for(int i = 2 ; i <= n ; ++ i)
        b[i] = (k + i - 1) * b[i - 1] % mod * pw(i, mod - 2) % mod;

    for(int i = 0 ; i < n ; ++ i)
        scanf("%lld", &a[i]);

    int len = 1; while(len <= n) len <<= 1;
    int output_n = n; n = len;

    sol(a, b, c, n);

    for(int i = 0 ; i < output_n ; ++ i)
        printf("%lld\n", (c[i] + mod) % mod);
}

