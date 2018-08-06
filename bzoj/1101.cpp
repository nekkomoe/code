#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 50000 + 10;

int n, m, d, mu[N], vis[N], p[N], tot;

void sol() {
    ll ans = 0;
    scanf("%d%d%d", &n, &m, &d); if(n > m) swap(n, m);
    n /= d, m /= d;
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (ll) (mu[j] - mu[i - 1]) * (n / i) * (m / i);
    }
    printf("%lld\n", ans);
}

int main() {
    mu[1] = 1;
    for(int i = 2 ; i <= 50000 ; ++ i) {
        if(!vis[i]) mu[i] = -1, p[++ tot] = i;
        for(int j = 1 ; j <= tot && (ll) i * p[j] <= 50000 ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
            mu[i * p[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
    int T; scanf("%d", &T);
    while(T --) sol();
}
