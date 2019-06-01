#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10, mod = 1e9 + 7;

int n, k;
ll b[N], pw[N];
int pri[N], mu[N], tot, vis[N];

ll gep(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int main() {
    scanf("%d%d", &n, &k);

    mu[1] = 1;
    for(int i = 2 ; i <= k ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= k ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    }

    for(int i = 1 ; i <= k ; ++ i) {
        pw[i] = gep(i, n);
    }

    for(int d = 1 ; d <= k ; ++ d) {
        for(int i = 1 ; i * d <= k ; ++ i) {
            // [i * d, (i + 1) * d)

            b[i * d] = (b[i * d] + pw[i] * mu[d] % mod) % mod;
            b[i * d] = (b[i * d] - pw[i - 1] * mu[d] % mod) % mod;
        }
    }

    for(int i = 1 ; i <= k ; ++ i) {
        b[i] = (b[i - 1] + b[i]) % mod;
        if(b[i] < 0) {
            b[i] += mod;
        }

        // printf("%lld ", b[i]);
    }
    // puts("");

    ll ans = 0;
    for(int i = 1 ; i <= k ; ++ i) {
        ans += b[i] ^ i;
        ans %= mod;
    }
    printf("%lld\n", ans);
}
