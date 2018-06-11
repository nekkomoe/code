#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int N = 50000 + 10, mod = 1e9 + 7;

int mu[N], p[N], tot, vis[N], n, m;

ll f[N];

void sol() {
    ll ans = 0;
    scanf("%d%d", &n, &m); if(n > m) swap(n, m);
    for(int i = 1, last ; i <= n ; i = last + 1) {
        last = min(n / (n / i), m / (m / i));
        ans += (ll) (mu[last] - mu[i - 1]) * f[n / i] * f[m / i];
    }
    printf("%lld\n", ans);
}

int main() {
    mu[1] = 1;
    for(int i = 2 ; i <= 50000 ; ++ i) {
        if(!vis[i]) p[++ tot] = i, mu[i] = -1;
        for(int j = 1 ; j <= tot && (ll) i * p[j] <= 50000 ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
            mu[i * p[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
    for(int i = 1 ; i <= 50000 ; ++ i) {
        for(int j = 1, last ; j <= i ; j = last + 1) {
            last = i / (i / j);
            f[i] += (ll) i / j * (last - j + 1);
        }
    }
    int T; scanf("%d", &T);
    while(T --) sol();
}
