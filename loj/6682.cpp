#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, inv2 = (mod + 1) / 2, inv3 = (mod + 1) / 3, N = 3e5 + 10, inv6 = (ll) inv2 * inv3 % mod;

ll n, sqr, ind_sma[N], ind_big[N], w[N], wcnt;
ll get(ll x) {
    return x <= sqr ? ind_sma[x] : ind_big[n / x];
}

ll g1[N], pri[N], tot, vis[N], sp1[N];

void init(ll n) {
    for(ll i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            sp1[tot] = (sp1[tot - 1] + 1) % mod;
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
    ll res = (g1[pos] - 4 * sp1[k]) % mod;
    for(int i = k + 1 ; i <= tot && (ll) pri[i] * pri[i] <= n ; ++ i) {
        ll pro = pri[i];
        for(int j = 1 ; pro <= n ; ++ j, pro *= pri[i]) {
            (res += (ll) (j + 1) * (j + 1) % mod * (S(n / pro, i) + (j != 1)) % mod) %= mod;
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
        g1[wcnt] = (x % mod - 1);
        x <= sqr ? (ind_sma[x] = wcnt) : (ind_big[n / x] = wcnt);
        // printf("w[%lld] = %lld\n", x, g1[wcnt]);
    }

    for(int i = 1 ; i <= tot ; ++ i) {
        for(int j = 1 ; j <= wcnt && (ll) pri[i] * pri[i] <= w[j] ; ++ j) {
            int k = get(w[j] / pri[i]);
            (g1[j] -= (g1[k] - sp1[i - 1]) % mod) %= mod;
        }
    }

    for(int i = 1 ; i <= wcnt ; ++ i) {
        (g1[i] *= 4) %= mod;
        // printf("%lld\n", g1[i]);
    }

    if(n == 1) {
        puts("0");
    } else {

        // printf("S = %lld\n", S(n, 0) + 1);

        ll ans = S(n, 0) + 1 - ([&] (ll n) {
            ll res = 0;
            for(ll i = 1, j ; i <= n ; i = j + 1) {
                j = n / (n / i);
                (res += (n / i) % mod * ((j - i + 1) % mod) % mod) %= mod;
            }
            return res;
        }) (n);
        ans = (ans % mod * inv2 % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}
