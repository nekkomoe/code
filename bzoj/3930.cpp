#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll n, k, L, H, ans; 

const int T = 2e6, N = T + 10;
int mu[N], vis[N], pri[N], tot;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

map<ll, ll> hs;

ll getmu(ll x) {
    if(x <= T) return mu[x];
    if(hs.count(x)) return hs[x];
    ll res = 0;
    for(ll i = 2, j ; i <= x ; i = j + 1) {
        j = x / (x / i);
        res += (j - i + 1) % mod * getmu(x / i) % mod;
        res %= mod;
    }
    return hs[x] = 1 - res;
}

int main() {
    cin >> n >> k >> L >> H;
    
    L = (L - 1) / k;
    H /= k;
    
    mu[1] = 1;
    for(ll i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
    
    
    for(ll t = 1, nxtt ; t <= H ; t = nxtt + 1) {
        nxtt = H / (H / t);
        if(L >= t) nxtt = min(nxtt, L / (L / t));
        ll x = H / t;
        ll y = L / t;
        ans += (getmu(nxtt) - getmu(t - 1)) % mod * pw((x - y) % mod, n) % mod;
        ans %= mod;
    }
    
    cout << (ans % mod + mod) % mod << endl;
}

