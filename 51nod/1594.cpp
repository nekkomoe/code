#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e6 + 10;

int pri[N], phi[N], mu[N], tot;

void init(int n) {
    mu[1] = phi[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!phi[i]) {
            phi[i] = i - 1;
            mu[i] = -1;
            pri[++ tot] = i;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
                mu[i * pri[j]] = -mu[i];
            }
        }
    }
}

ll f[N], g[N];

ll sol(int n) {
    for(int i = 1 ; i <= n ; ++ i) {
        f[i] = 0;
        ++ f[phi[i]];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + i ; j <= n ; j += i) {
            f[i] += f[j];
        }
        f[i] *= f[i];
    }
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ll g = 0;
        for(int j = i ; j <= n ; j += i) {
            g += f[j] * mu[j / i];
        }
        ans += phi[i] * g;
    }
    return ans;
}

int main() {
    init(2e6);
    int t; scanf("%d", &t);
    while(t --) {
        int n; scanf("%d", &n);
        printf("%lld\n", sol(n));
    }
}
