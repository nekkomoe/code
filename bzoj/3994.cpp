#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 50000;

int n, m, T, mu[N + 5], sig[N + 5], vis[N + 5], prime[N + 5], p, ct[N + 5];

void build() {
    mu[1] = sig[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        if(!vis[i]) {
            prime[++ p] = i;
            mu[i] = -1, sig[i] = 2, ct[i] = 1;
        }
        for(int j = 1 ; j <= p ; ++ j) {
            if(prime[j] * i > N) break;
            vis[prime[j] * i] = 1;
            if(i % prime[j]) {
                mu[i * prime[j]] = -mu[i];
                sig[i * prime[j]] = sig[i] * 2;
                ct[i * prime[j]] = 1;
            } else {
                sig[i * prime[j]] = sig[i] / (ct[i] + 1) * (ct[i] + 2);
                ct[i * prime[j]] = ct[i] + 1;
                break;
            }
        }
    }
    for(int i = 1 ; i <= N ; ++ i) mu[i] += mu[i - 1], sig[i] += sig[i - 1];
}

void sol() {
    ll ans = 0;
    for(int i = 1, j ; i <= min(n, m) ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (ll) (mu[j] - mu[i - 1]) * sig[n / i] * sig[m / j];
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &T);
    build();
    while(T --) {
        scanf("%d%d", &n, &m), sol();
    }
}
