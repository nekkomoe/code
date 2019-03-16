// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int lim = 1e7, N = lim + 10, mod = 1e9 + 7;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
bool vis[N]; ll ans, n;
int pri[N], mu[N], tot;

void init(int n) {
    mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; i * pri[j] <= n && j <= tot ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
}

map<ll, ll> mem;
ll sol(ll n) {
    if(n <= lim) return mu[n];
    if(mem.count(n)) return mem[n];
    ll res = 1;
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = (res - sol(n / i) * (j - i + 1) % mod) % mod;
    }
    return mem[n] = res;
}

int main() {
    init(lim);
    scanf("%lld", &n);
    for(ll d = 1, nxtd, lst = 0 ; d <= n ; d = nxtd + 1) {
        nxtd = n / (n / d);
        ll cur = sol(nxtd);
        ans = (ans + (pw(2, n / d % (mod - 1)) - 1) * (cur - lst) % mod) % mod;
        lst = cur;
    }
    printf("%lld\n", (ans + mod) % mod);
}
