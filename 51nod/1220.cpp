#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6, mod = 1e9 + 7;

ll e[N + 10], d[N + 10], muid[N + 10], mu[N + 10];

int pri[N + 10], tot, vis[N + 10];

ll n, ans;

map<ll, ll> val_sig;

ll sum_sig1(ll n) {
    if(n <= N) {
        return d[n];
    } else {
        if(val_sig.find(n) != val_sig.end()) {
            return val_sig[n];
        } else {
            ll res = 0;
            for(ll i = 1, j ; i <= n ; i = j + 1) {
                j = n / (n / i);
                res = (res + (i + j) * (j - i + 1) / 2 * (n / i) % mod) % mod;
            }
            return val_sig[n] = res;
        }
    }
}

map<ll, ll> val_muid;

ll sum_muid(ll n) {
    if(n <= N) {
        return muid[n];
    } else {
        if(val_muid.find(n) != val_muid.end()) {
            return val_muid[n];
        } else {
            ll res = 1;
            for(ll i = 2, j ; i <= n ; i = j + 1) {
                j = n / (n / i);
                res = (res - (i + j) * (j - i + 1) / 2 % mod * sum_muid(n / i)) % mod;
            }
            return val_muid[n] = res;
        }
    }
}

int main() {
    scanf("%lld", &n);

    d[1] = 1;
    mu[1] = 1;
    muid[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        if(!vis[i]) {
            d[i] = 1 + i;
            e[i] = 1 + i;
            mu[i] = -1;
            pri[++ tot] = i;
        }
        for(int j = 1 ; j <= tot && (ll) i * pri[j] <= N ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                d[i * pri[j]] = d[i] / e[i] * (pri[j] * e[i] + 1);
                e[i * pri[j]] = pri[j] * e[i] + 1;
                break;
            } else {
                d[i * pri[j]] = d[i] * (1 + pri[j]);
                e[i * pri[j]] = 1 + pri[j];
                mu[i * pri[j]] = -mu[i];
            }
        }
        d[i] = (d[i] + d[i - 1]) % mod;
        muid[i] = (muid[i - 1] + mu[i] * i) % mod;
    }
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        ll sig = sum_sig1(n / i) % mod;
        sig = sig * sig % mod;
        ll mui = (sum_muid(j) - sum_muid(i - 1)) % mod;
        ans = (ans + mui % mod * sig % mod) % mod;
    }

    printf("%lld\n", (ans % mod + mod) % mod);
}
