#include "bits/stdc++.h"
using namespace std;
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e6; const ll mod = 1e9 + 7;
ll n, inv2, phi[N + 10], pri[N + 10], tot, vis[N + 10];
map<ll, ll> val;

ll sol(ll n) {
    if(n <= N) return phi[n];
    if(val.find(n) != val.end()) return val[n];
    ll x = n % mod;
    ll res = (1 + x) % mod * x % mod * inv2 % mod;
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = (res - sol(n / i) % mod * (j - i + 1) % mod) % mod;
    }
    res = (res % mod + mod) % mod;
    return val[n] = res;
}

int main() {
    inv2 = 5e8 + 4;
    phi[1] = 1;
    for(ll i = 2 ; i <= N ; ++ i) {
        if(!vis[i]) phi[i] = i - 1, pri[++ tot] = i;
        for(ll j = 1 ; j <= tot && i * pri[j] <= N ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            }
            phi[i * pri[j]] = phi[i] * (pri[j] - 1);
        }
        phi[i] = (phi[i] + phi[i - 1]) % mod;
    }
    scanf("%lld", &n);
    printf("%lld", sol(n));
}

