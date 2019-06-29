#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e7 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

int vis[N], pri[N], tot, mu[N];

void init(int n) {
    mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            mu[pri[++ tot] = i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    }
}

int main() {
    ll n; scanf("%lld", &n);
    init(min(N, int(cbrt(n) + 2)));
    ll cnt = 0, sum = 0;
    for(ll i = 1 ; i * i <= n ; ++ i) {
        for(ll j = 1 ; i * i * j * j * j <= n ; ++ j) {
            if(mu[j]) {
                ++ cnt;
                sum += i * i * j * j * j;
            }
        }
    }
    printf("%lld\n%lld\n", cnt, sum);
}
