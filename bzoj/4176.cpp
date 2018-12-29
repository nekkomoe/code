#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int T = 1e7, N = T + 10, mod = 1e9 + 7;
 
int mu[N], pri[N], tot, vis[N];
 
map<ll, ll> val;
ll sol(ll n) {
    if(n <= T) return mu[n];
    if(val.count(n)) return val[n];
    ll res = 1;
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        (res -= (j - i + 1) % mod * sol(n / i) % mod) %= mod;
    } 
    return val[n] = res;
}
 
ll c(ll n) {
    ll x = (1 + n) * n / 2 % mod;
    return x * x % mod;
}
 
ll F(ll n) {
    ll res = 0;
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        (res += n / i % mod * (j - i + 1) % mod) %= mod;
    } 
    return res * res % mod; 
}
 
int main() {
    ios :: sync_with_stdio(0);
    mu[1] = 1;
    for(int i = 2 ; i <= T ; ++ i) {
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
    ll ans = 0, n;
    cin >> n;
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        (ans += F(n / i) % mod * (sol(j) - sol(i - 1)) % mod) %= mod;
    }
    cout << (ans % mod + mod) % mod << endl;
}

