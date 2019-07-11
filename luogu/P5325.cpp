// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, inv2 = (mod + 1) / 2, inv3 = (mod + 1) / 3, N = 3e5 + 10, inv6 = (ll) inv2 * inv3 % mod;

ll n, sqr, ind_sma[N], ind_big[N], w[N], wcnt;
ll get(ll x) {
    return x <= sqr ? ind_sma[x] : ind_big[n / x];
}

ll g1[N], g2[N], pri[N], tot, vis[N];
ll calc_sqr_sum(ll n) {
    n %= mod;
    return n * (n + 1) % mod * inv2 % mod;
}
ll calc_cub_sum(ll n) {
    n %= mod;
    return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}
ll sp1[N], sp2[N];
void init(ll n) {
    for(ll i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            sp1[tot] = (sp1[tot - 1] + i) % mod;
            sp2[tot] = (sp2[tot - 1] + i * i % mod) % mod;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                break;
            }
        }
    }
}

ll S(ll n, int k) {
    if(pri[k] >= n) {
        return 0;
    }
    int pos = get(n);
    ll res = ((g2[pos] - g1[pos]) - (sp2[k] - sp1[k])) % mod;
    for(int i = k + 1 ; i <= tot && (ll) pri[i] * pri[i] <= n ; ++ i) {
        ll pro = pri[i];
        for(int j = 1 ; pro <= n ; ++ j, pro *= pri[i]) {
            ll val = pro % mod; val = val * (val - 1) % mod;
            (res += val * (S(n / pro, i) + (j != 1)) % mod) %= mod;
        }
    }
    return res;
}

int main() {
    scanf("%lld", &n);
    sqr = sqrt(n);
    init(sqr);

    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        ll x = w[++ wcnt] = n / i;
        g1[wcnt] = calc_sqr_sum(x) - 1;
        g2[wcnt] = calc_cub_sum(x) - 1;
        x <= sqr ? (ind_sma[x] = wcnt) : (ind_big[n / x] = wcnt);
    }

    for(int i = 1 ; i <= tot ; ++ i) {
        for(int j = 1 ; j <= wcnt && (ll) pri[i] * pri[i] <= w[j] ; ++ j) {
            int k = get(w[j] / pri[i]);
            (g1[j] -= pri[i] * (g1[k] - sp1[i - 1]) % mod) %= mod;
            (g2[j] -= pri[i] * pri[i] % mod * (g2[k] - sp2[i - 1]) % mod) %= mod;
        }
    }

    printf("%lld\n", ((S(n, 0) + 1) % mod + mod) % mod);
}
