#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7, N = 1e5 + 10;
 
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
 
void upd(ll &a, ll b) {
    a = (a + b) % mod;
}
 
int n;
ll fac[N], invfac[N];
vector<int> g[N];
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}
 
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[n - m] % mod;
}
 
ll ans;
int k;
int main() {
    init(N - 1);
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ans = k;
    for(int i = 1 ; i <= n ; ++ i) {
        int sz = g[i].size() - (i > 1);
        ans = ans * C(k - 1 - (i > 1), sz) % mod;
    }
    printf("%lld\n", ans);
}
