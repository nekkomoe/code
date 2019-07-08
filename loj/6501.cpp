#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 1e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

ll fac[N], invfac[N];
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i >= 1 ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    init(N - 1);
    int t; scanf("%d", &t);
    while(t --) {
        int n, m; scanf("%d%d", &n, &m);
        printf("%lld\n", C(n, m) * pw(2, n - m) % mod);
    }
}
