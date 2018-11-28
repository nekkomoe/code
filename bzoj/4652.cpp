#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, k;
const int T = 5e6, N = T + 10;
ll mu[N], sum[N], vis[N], pri[N], tot;

void init() {
    mu[1] = 1;
    for(ll i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(ll j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                break;
            }
            mu[i * pri[j]] = -mu[i];
        }
    } 
    for(ll i = 1 ; i <= T ; ++ i) sum[i] = sum[i - 1] + mu[i];
}

map<ll, ll> val;
ll get(ll n) {
    if(n <= T) return sum[n];
    if(val.find(n) != val.end()) return val[n];
    ll res = n >= 1;
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res -= (j - i + 1) * get(n / i);
    }
    return val[n] = res;
}

vector<ll> sig;

map<pair<ll, pair<ll, ll> >, ll> mem;

ll f(ll n, ll m, ll k) {
    if(!n || !m) return 0;
    pair<ll, pair<ll, ll> > hs = make_pair(n, make_pair(m, k));
    if(mem.find(hs) != mem.end()) return mem[hs];
    
    ll res = 0;
    if(k == 1) {
        for(ll i = 1, j ; i <= min(n, m) ; i = j + 1) {
            j = min(n / (n / i), m / (m / i));
            res += (n / i) * (m / i) * (get(j) - get(i - 1));
        }
    } else {
        for(ll t = 0 ; t < sig.size() ; ++ t) {
            ll i = sig[t];
            if(mu[i] && k % i == 0) {
                res += mu[i] * f(m / i, n, i);
            }
        } 
    }
    
    return mem[hs] = res;
}

int main() {
    init();
    cin >> n >> m >> k;
    for(ll i = 1 ; i * i <= k ; ++ i)
        if(k % i == 0) {
            sig.push_back(i);
            if(k / i != i) sig.push_back(k / i);
        }
    cout << f(n, m, k) << endl;
}

