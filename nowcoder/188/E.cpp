#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5000000 + 10, mod = 998244353;
 
int n = 5000000, m;
ll f[N], d[N], k;
int mu[N], pri[N], tot; bool vis[N];
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
 
void init() {
    mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                break;
            } else {
                mu[i * pri[j]] = -mu[i];
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) d[i] = pw(i, k);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i ; j <= n ; j += i) {
            f[j] = (f[j] + d[i] * mu[j / i] % mod) % mod;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        f[i] = (f[i] % mod + mod) % mod;
    }
}
 
int main() {
    scanf("%d%lld", &m, &k);
    init();
    while(m --) {
        int x; scanf("%d", &x);
        printf("%d\n", f[x]);
    }
}
