#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 1e5 + 10, mod = 998244353;

int n, k;

ll prisig[N], expprisig[N]; int prisigcnt;

ll d[N]; int dcnt;
void dfs(int u, ll prod) {
    if(prod > n) {
        return ;
    } else if(u == prisigcnt) {
        d[++ dcnt] = prod;
    } else {
        for(int i = 0 ; i <= expprisig[u + 1] ; ++ i) {
            dfs(u + 1, prod);
            prod *= prisig[u + 1];
        }
    }
}

ll f[1010], ans, inv[N], g[1010];

ll read() {
    ll x = 0; char c = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}

int main() {
    n = read(), k = read();
    inv[0] = inv[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for(int i = 1 ; i <= k ; ++ i) {
        ll T = read(), At = read();

        prisigcnt = 0;
        ll T_tmp = T;
        for(ll v = 2 ; v * v <= T_tmp ; ++ v)
            if(T_tmp % v == 0) {
                prisig[++ prisigcnt] = v, expprisig[prisigcnt] = 0;
                while(T_tmp % v == 0) T_tmp /= v, ++ expprisig[prisigcnt];
            }
        if(T_tmp > 1) prisig[++ prisigcnt] = T_tmp, expprisig[prisigcnt] = 1;

        // [ [T/n], n ]
        ll lim = T / n + (T % n != 0);
        dcnt = 0;
        dfs(0, 1);        
        
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        int all = (1 << prisigcnt) - 1;
        for(int j = 1 ; j <= dcnt ; ++ j) {
            ll x = d[j];
            if(x < lim) continue;
            int sta = 0;
            for(int k = 1 ; k <= prisigcnt ; ++ k)
                if(x % prisig[k] == 0)
                    sta |= 1 << (k - 1);
            (f[sta] += inv[x]) %= mod;
            g[sta] = f[sta];
        }
        ll val = 0;
        for(int i = 1 ; i <= prisigcnt ; ++ i)
            for(int s = 0 ; s <= all ; ++ s)
                if(s & (1 << (i - 1)))
                    (f[s] += f[s - (1 << (i - 1))]) %= mod;
        for(int s = 0 ; s <= all ; ++ s)
            (val += g[s] * f[all - s] % mod) %= mod;
        ans = (ans + At * val % mod * (T % mod) % mod) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
}
