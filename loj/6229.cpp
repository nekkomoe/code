#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int T = 5e6, N = T + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2), inv6 = pw(6, mod - 2);
ll calc1(ll n) {
    return (n % mod) * (n % mod + 1) % mod * inv2 % mod;
}

ll calc2(ll n) {
    return (n % mod) * (n % mod + 1) % mod * (2 * n % mod + 1) % mod * inv6 % mod;
}

ll calc3(ll n) {
    ll x = calc1(n);
    return x * x % mod;
}

ll n, ans;

ll phi[N], pri[N], tot, vis[N];

ll ins[N], val[N];

map<ll, ll> hs;

ll getsum(ll n) {
    if(n <= T) return phi[n];
    if(ins[:: n / n]) return val[:: n / n]; ins[:: n / n] = 1;
    ll res = calc3(n);
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = (res - (calc2(j) - calc2(i - 1)) % mod * getsum(n / i) % mod) % mod;
    }
    return val[:: n / n] = res;
}

int main() {
    
    cin >> n; 
    
    phi[1] = 1;
    for(int i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) pri[++ tot] = i, phi[i] = i - 1;
        for(int j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j] % mod;
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1) % mod;
            }
        }
        phi[i] = phi[i] * i % mod * i % mod;
        phi[i] = (phi[i - 1] + phi[i]) % mod;
    }
    
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        ans = (ans + (j - i + 1) % mod * getsum(n / i) % mod) % mod;
    }
    
    ans = (ans + n) % mod * inv2 % mod;
    
    if(ans < 0) ans += mod;
    cout << ans << endl;
}

