#include <bits/stdc++.h>
using namespace std;
// typedef unsigned long long ll;
typedef long long ll;
const int N = 46415 + 10, mod = 1e9 + 7;
ll n, m, ans;

// ---------------
ll mu[N], pri[int(1e7) + 10], calc[int(4e5) + 10];
bool vis[int(4e5) + 10], vvv[N];
int tot;
void init() {
    mu[1] = 1;
    for(int i = 2 ; i < N ; ++ i) {
        if(!vvv[i]) mu[i] = - 1, pri[++ tot] = i;
        for(int j = 1 ; j <= tot && i * pri[j] < N ; ++ j) {
            vvv[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            else mu[i * pri[j]] = -mu[i];
        }
    }
    for(int i = 1 ; i < N ; ++ i) mu[i] += mu[i - 1];
}
// ---------------

ll sol(ll x) {
    if(x < N) return mu[x];
    if(vis[m / x]) return calc[m / x];
    ll sum = vis[m / x] = 1;
    for(ll i = 2, j ; i <= x ; i = j + 1) {
        j = x / (x / i);
        sum -= sol(x / i) * (j - i + 1) % mod;
        sum %= mod;
    }
    return calc[m / x] = sum;
}

inline ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}

int main() {
    ios :: sync_with_stdio(0);
    init();
    cin >> m;
    ans = 1;
    for(ll i = 2, j ; i <= m ; i = j + 1) {
        j = m / (m / i);
        // printf("[%lld, %lld] = %lld\n", i, j, (sol(j) - sol(i - 1)));
        ans -= (m / i) % mod * pw((m - m / i) % mod, mod - 2) % mod * (sol(j) - sol(i - 1)) % mod;
        ans %= mod;
    }
    ans = (ans + mod) % mod;
    cout << ans;
}
