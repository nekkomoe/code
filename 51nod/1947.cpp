#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll calcfac(ll n) {
    ll r = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        r = r * i % mod;
    }
    return r;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll C(int n, int m) {
    return n < m || m < 0 ? 0 : calcfac(n) * pw(calcfac(n - m), mod - 2) % mod * pw(calcfac(m), mod - 2) % mod;
}

int main() {
    ll n; cin >> n;
    ll ans = (C(2 * n - 1, n - 1) + pw(4, n - 1)) % mod * n % mod * pw(2, mod - 2) % mod;
    cout << (ans % mod + mod) % mod << endl;
}
