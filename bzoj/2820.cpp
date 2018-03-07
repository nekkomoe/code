#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 10000005;

int n, a, b, c, d, k, mu[N], vis[N], prime[N], p;

ll f[N];

void build() {
    mu[1] = 1;
    for(int i = 2 ; i <= N - 5 ; ++ i) {
        if(!vis[i]) prime[++ p] = i, mu[i] = -1;
        for(int j = 1 ; j <= p ; ++ j) {
            if(i * prime[j] > N - 5) break;
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else break;
        }
    }
    for(int i = 1 ; i <= p ; ++ i) for(int j = 1 ; (ll) j * prime[i] <= (ll) (N - 5) ; ++ j) f[j * prime[i]] += mu[j];
    for(int i = 1 ; i <= N - 5 ; ++ i) f[i] += f[i - 1];
    for(int i = 1 ; i <= N - 5 ; ++ i) mu[i] += mu[i - 1];
}

void sol() {
    int n = a, m = b;
    ll ans = 0;
    for(int i = 1, j ; i <= min(n, m) ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (f[j] - f[i - 1]) * (n / i) * (m / j);
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &n);
    build();
    while(n --) {
        scanf("%d%d", &a, &b), sol();
    }
}
