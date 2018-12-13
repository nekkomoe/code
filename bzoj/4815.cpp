// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 4e6 + 10;

int n, m;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int L[N], R[N], id[N], len, cnt;

ll sum[N], locsum[N], a[N];

void initfafa() {
    len = max((int) sqrt(n), 1);
    for(int i = 1 ; i <= n ; ++ i) {
        cnt = id[i] = (i - 1) / len + 1;
        if(!L[cnt]) L[cnt] = i;
        R[cnt] = i;
        sum[i] = a[i] = (ll) i * i % mod;
        (locsum[cnt] += sum[i]) %= mod;
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        (locsum[i] += locsum[i - 1]) %= mod;
        for(int j = L[i] + 1 ; j <= R[i] ; ++ j) {
            (sum[j] += sum[j - 1]) %= mod;
        }
    }
} 

void poi(int x, int v) {
    for(int i = id[x] ; i <= cnt ; ++ i) {
        (locsum[i] += (v - a[x]) % mod) %= mod;
    }
    a[x] = v;
    int l = L[id[x]], r = R[id[x]];
    sum[l] = a[l];
    for(int i = l + 1 ; i <= r ; ++ i) {
        sum[i] = (a[i] + sum[i - 1]) % mod;
    }
}

ll ask(int x) {
    return (locsum[id[x] - 1] + sum[x]) % mod;
}

ll phi[N], vis[N], pri[N], tot, FAFA[N];
void init() {
    phi[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            phi[i] = i - 1;
            pri[++ tot] = i;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j] % mod;
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1) % mod;
            }
        }
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        FAFA[i] = (FAFA[i - 1] + (ll) i * i % mod * phi[i] % mod) % mod;
    }
}

ll sol(int k) {
    ll res = 0;
    for(int d = 1, newd ; d <= k ; d = newd + 1) {
        newd = k / (k / d);
        ll sum = (ask(newd) - ask(d - 1)) % mod;
        res = (res + sum * FAFA[k / d]) % mod;
    }
    return res;
}

int main() {
    scanf("%d%d", &m, &n);
    init();
    initfafa();
    for(int i = 1 ; i <= m ; ++ i) {
        int a, b, k; ll x;
        scanf("%d%d%lld%d", &a, &b, &x, &k);
        x %= mod;
        int d = gcd(a, b);
        poi(d, pw((ll) a * b % mod, mod - 2) * d % mod * d % mod * x % mod);
        printf("%lld\n", (sol(k) % mod + mod) % mod);
    }
} 

