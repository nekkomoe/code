#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 998244353;
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
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
ll calc(int n, int m) {
    return n < 0 ? 0 : C(n, n / 2 + m / 2);
}

int main() {
    init(N - 10);
    ll n, m; cin >> n >> m;
    if(n < m) puts("0");
    else {
        ++ m, n *= 2;
        ll ans = (calc(n, 0) - calc(n, 2 * m) - calc(n, 2)) % mod;
        for(int i = 2 * (m + 1) ; i <= n ; i += 2 * (m + 1)) {
            ans += 2 * calc(n, i) - calc(n, i + 2 * m) - calc(n, i + 2);
            ans %= mod;
        }
        cout << (ans % mod + mod) % mod << endl;
    }
}
