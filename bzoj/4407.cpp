#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5e6, mod = 1e9 + 7;

int pri[N + 10], tot, vis[N + 10], g[N + 10], f[N + 10], F[N + 10], n, m, k, T;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}

void sol() {
    scanf("%d%d", &n, &m);
    int ans = 0;
    if(n > m) swap(n, m);
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans = ((ll) ans + (ll) (F[j] - F[i - 1]) % mod * (n / i) % mod * (m / i) % mod) % mod;
    }
    printf("%d\n", (ans % mod + mod) % mod);
}

int main() {
    scanf("%d%d", &T, &k);
    F[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        if(!vis[i]) g[i] = i, pri[++ tot] = i, f[i] = pw(i, k), F[i] = f[i] - 1;
        for(int j = 1 ; j <= tot && (ll) i * pri[j] <= N ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                g[i * pri[j]] = g[i] * pri[j];
                F[i * pri[j]] = g[i] == i ? (ll) F[i] * f[pri[j]] % mod : (ll) F[i / g[i]] * F[g[i] * pri[j]] % mod;
                break;
            }
            g[i * pri[j]] = pri[j];
            F[i * pri[j]] = (ll) F[i] * F[pri[j]] % mod;
        }
    }
    for(int i = 2 ; i <= N ; ++ i) F[i] = ((ll) F[i] + F[i - 1]) % mod;
    while(T --) sol();
}
