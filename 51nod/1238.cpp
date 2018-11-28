#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int T = 5e6, N = T + 10, mod = 1e9 + 7;

ll phi[N], sum[N], vis[N], pri[N], tot;

map<ll, ll> val;

ll pw(ll a, ll b) {
    ll r = 1;
    a %= mod;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2), inv4 = pw(4, mod - 2), inv6 = pw(6, mod - 2);

ll calc(ll n) {
    if(n <= 0) return 0;
    n %= mod;
    return n * (n + 1) % mod * (2 * n % mod + 1) % mod * inv6 % mod;
}

ll S(ll n) {
    if(n <= T) return sum[n];
    else if(val.find(n) != val.end()) return val[n];
    ll res = pw(n, 2) * pw(n + 1, 2) % mod * inv4 % mod;
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = (res - (calc(j) - calc(i - 1)) % mod * S(n / i)) % mod;
    }
    return val[n] = res;
}

void init() {
    phi[1] = 1;
    for(ll i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            phi[i] = i - 1;
        }
        for(ll j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j] % mod;
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1) % mod;
            }
        }
    }
    for(ll i = 1 ; i <= T ; ++ i) {
        sum[i] = (sum[i - 1] + (phi[i] * i % mod * i % mod)) % mod;
    }
}

ll f(ll n) {
    if(n <= 0) return 0;
    n %= mod;
    return (1 + n) * n % mod * inv2 % mod;
}

int main() {
    init();
    ll n, ans = 0; cin >> n;
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        ans = (ans + (f(j) - f(i - 1)) % mod * S(n / i)) % mod;
    }
    cout << (ans % mod + mod) % mod << endl;
}

