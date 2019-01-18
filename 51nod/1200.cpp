#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7, N = 1 << 22;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2);

int n, m; ll a[N], b[N];

int vis[N], pri[N], tot;

void fwt(ll *f, int n, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1)
        for(int j = 0 ; j + i / 2 < n ; j += i)
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) f[k] = (u + v) % mod, f[k + i / 2] = (u - v) % mod;
                else f[k] = (u + v) * inv2 % mod, f[k + i / 2] = (u - v) * inv2 % mod;
            }
}

int main() {
    
    for(int i = 2 ; i <= 50000 ; ++ i)
        if(!vis[i]) {
            pri[++ tot] = i;
            for(int j = i ; j <= 50000 ; j += i) {
                vis[j] = 1;
            }
        }

    while(scanf("%d%d", &n, &m) == 2) {
        int len = 1;
        while(len <= m) len <<= 1;
        for(int i = 0 ; i < len ; ++ i) a[i] = 0;
        for(int i = 1 ; i <= tot && pri[i] <= m ; ++ i) a[pri[i]] = 1;
        fwt(a, len, 0);
        for(int i = 0 ; i < len ; ++ i) a[i] = pw(a[i], n);
        fwt(a, len, 1);
        printf("%lld\n", (a[0] + mod) % mod);
    }
}


