#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 998244353;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll fac[N], invfac[N];

ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    ll n, x, y, p, ans = 0;
    cin >> n >> x >> y;
    p = x * pw(y, mod - 2) % mod;
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    for(int i = 0 ; i <= n ; ++ i) {
        ans = (ans + C(n, i) * pw(p, (ll) i * (i - 1) / 2) % mod) % mod;
    }
    cout << (ans % mod + mod) % mod << endl;
}
