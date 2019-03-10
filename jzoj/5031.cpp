#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, k; ll f[N], g[N], h[N], tmp[N];

void calc(ll *f, ll *g) {
    ll *h = tmp; memset(tmp, 0, sizeof tmp);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j * i <= n ; ++ j)
            (h[i * j] += f[i] * g[j]) %= mod;
    for(int i = 1 ; i <= n ; ++ i) g[i] = h[i];
}

void sol() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i)
        scanf("%lld", &f[i]),
        g[i] = 1,
        h[i] = 0;
    h[1] = 1;
    for( ; k ; k >>= 1, calc(g, g))
        if(k & 1)
            calc(g, h);
    calc(f, h);
    for(int i = 1 ; i <= n ; ++ i) printf("%lld%c", (h[i] % mod + mod) % mod, i == n ? '\n' : ' ' );
}

int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    int T; scanf("%d", &T);
    while(T --) sol(); 
}

