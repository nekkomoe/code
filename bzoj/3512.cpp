#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int T = 1e6, N = T + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    a %= mod;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2);

map<ll, ll> poi[N];

ll phi[N], sumphi[N];
int vis[N], pri[N], tot;

ll n, m;
map<ll, ll> tra;

ll get(ll n) {
    ll &res = tra[n];
    if(n <= T) return sumphi[n];
    else if(res) return res;
    res = (n % mod) * (n % mod + 1) % mod * inv2 % mod;
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = (res - (j - i + 1) % mod * get(n / i) % mod) % mod;
    }
//    cout << "N = " << n << " res = " << res << endl;
    return res;
}

ll S(ll n, ll m) {
//    cout << n << ' ' << m << endl;
    if(m == 0) return 0;
    else if(n == 1) {
//        cout << "res get " << m << ": " << get(m) << endl;
        return get(m);
    }
    else if(poi[n][m]) return poi[n][m];
    ll res = 0;
    for(ll i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            ll j = n / i;
            res = (res + phi[j] * S(i, m / i) % mod) % mod;
            if(i != j) {
                res = (res + phi[i] * S(j, m / j) % mod) % mod;
            }
        }
    }
//    cout << n << ' ' << m << ' ' << res << endl;
    return poi[n][m] = res;
}

ll t[N];

void initphi() {
    phi[1] = 1;
    t[1] = 1;
    for(int i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) {
            vis[i] = 1;
            pri[++ tot] = i;
            phi[i] = i - 1;
            t[i] = i;
        }
        for(int j = 1 ; i * pri[j] <= T && j <= tot ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j] % mod;
                t[i * pri[j]] = t[i];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1) % mod;
                t[i * pri[j]] = t[i] * pri[j];
            }
        }
    }
    for(int i = 1 ; i <= T ; ++ i) {
        sumphi[i] = (sumphi[i - 1] + phi[i]) % mod;
    }
}

int main() {
    initphi();
     
    cin >> n >> m;
    
//    cout << S(n, m) << endl; return 0;
    
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ans = (ans + (ll) i / t[i] % mod * S(t[i], m) % mod) % mod;
    }
    cout << (ans % mod + mod) % mod << endl;
}

