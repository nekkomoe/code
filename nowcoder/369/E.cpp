#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int N = 250000 + 10, mod = 1e9 + 7;
 
int n, m;
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
 
ll f[N], g[N];
 
int pri[N], tot, mu[N], vis[N], cnt[N], prod[N];
 
ll pre[N], pre_inv[N];
 
void init(int n) {
    mu[1] = 1;
    g[1] = 0;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
            g[i] = 1;
            cnt[i] = 1, prod[i] = i;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                cnt[i * pri[j]] = cnt[i] + 1;
                prod[i * pri[j]] = prod[i] * pri[j];
                g[i * pri[j]] = g[i / prod[i]] + cnt[i] + 1;
                break;
            } else {
                cnt[i * pri[j]] = 1;
                prod[i * pri[j]] = pri[j];
                mu[i * pri[j]] = -mu[i];
                g[i * pri[j]] = g[i] + 1;
            }
        }
    }
    g[1] = 1;
    for(int i = 1 ; i <= n ; ++ i) f[i] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; i * j <= n ; ++ j) {
            ll val = 0;
            if(mu[j] == 0) {
                val = 1;
            } else if(mu[j] == -1) {
                val = pw(g[i], mod - 2);
            } else {
                val = g[i];
            }
            (f[i * j] *= val) %= mod;
        }
    }
     
    pre_inv[0] = pre[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        pre[i] = pre[i - 1] * f[i] % mod;
        pre_inv[i] = pw(pre[i], mod - 2);
    }
}
 
ll ask(int l, int r) {
    return pre[r] * pre_inv[l - 1] % mod;
}
 
void runprog() {
    scanf("%d%d", &n, &m);
    if(n > m) swap(n, m);
    ll ans = 1;
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        (ans *= pw(ask(i, j), (ll) (n / i) * (m / i))) %= mod;
    }
    printf("%lld\n", ans);
}
 
int main() {
    init(250000);
     
//    for(int i = 1 ; i <= 10 ; ++ i) printf("%lld %lld %d\n", f[i], g[i], mu[i]);
     
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
