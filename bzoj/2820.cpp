#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 10000000 + 10;

int p[N], tot, vis[N], mu[N], n, m;

ll f[N];

void sol() {
    ll ans = 0;
    scanf("%d%d", &n, &m); if(n > m) swap(n, m);
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (f[j] - f[i - 1]) * (n / i) * (m / i);
    }
    printf("%lld\n", ans);
}

int main() {
    mu[1] = 1;
    for(int i = 2 ; i <= 10000000 ; ++ i) {
        if(!vis[i]) vis[i] = 1, p[++ tot] = i, mu[i] = -1;
        for(int j = 1 ; j <= tot && (ll) i * p[j] <= 10000000 ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
            mu[i * p[j]] = -mu[i];
        }
    }
    for(int i = 1 ; i <= tot ; ++ i)
        for(int j = 1 ; (ll) p[i] * j <= 10000000 ; ++ j)
            f[p[i] * j] += mu[j];
    for(int i = 1 ; i <= 10000000 ; ++ i) f[i] += f[i - 1];
    int T; scanf("%d", &T);
    while(T --) sol();
}
