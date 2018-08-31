#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int mu[N], vis[N], p[N], tot;

ll calc(ll n) {
    return n * (n + 1) / 2;
}

void sol() {
    int n, m;
    scanf("%d%d", &n, &m);
    ll res = 0;
    if(n > m) swap(n, m);
    for(int i = 1 ; i <= n ; ++ i) {
        res += (ll) mu[i] * (n / i) * (m / i);
    }
    printf("%lld\n", res);
}

int main() {
    mu[1] = 1;
    for(int i = 2 ; i < N ; ++ i) {
        if(!vis[i]) mu[i] = -1, p[++ tot] = i;
        for(int j = 1 ; j <= tot && i * p[j] < N ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
            mu[i * p[j]] = -mu[i];
        }
    }
    int T; scanf("%d", &T);
    while(T --) sol();
}
