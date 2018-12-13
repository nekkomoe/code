#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 9;

const int s5 = 616991993;

ll pw(ll a, ll b) {
    ll res = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            res = res * a % mod;
    return res;
}

const int N = 1e5 + 10;

ll fac[N], invfac[N];

ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

const ll a = (1 + s5) * pw(2, mod - 2) % mod;
const ll b = (1 - s5) * pw(2, mod - 2) % mod;

void sol() {
    ll n, k; cin >> n >> k;
    ll ans = 0;
    for(int j = 0 ; j <= k ; ++ j) {
        ll q = pw(a, j) * pw(b, k - j) % mod;
        if(q == 1) {
            ans += C(k, j) * pw(-1, k - j) % mod * (n % mod) % mod;
        } else {
            ans += C(k, j) * pw(-1, k - j) % mod * ((pw(q, n + 1) - q) % mod * pw(q - 1, mod - 2) % mod) % mod;
        }
        ans %= mod;
    }
    ans = ans * pw(pw(s5, mod - 2), k) % mod;
    cout << (ans % mod + mod) % mod << endl;
}

int main() {
    ios :: sync_with_stdio(0);
    const int T = 1e5;
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= T ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[T] = pw(fac[T], mod - 2);
    for(int i = T - 1 ; i >= 1 ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    int fafa; cin >> fafa;
    while(fafa --) sol();
}

