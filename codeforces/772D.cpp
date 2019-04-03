#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e6 + 10, mod = 1e9 + 7;

int n;
ll cnt[N], sig[N], sig2[N], pw[N], f[N];

void fmt(int n) {
    for(int j = 1 ; j < n ; j *= 10) {
        for(int i = n - 1 ; ~ i ; -- i) {
            if((i / j) % 10) {
                (cnt[i - j] += cnt[i]) %= mod;
                (sig[i - j] += sig[i]) %= mod;
                (sig2[i - j] += sig2[i]) %= mod;
            }
        }
    }
}

void invfmt(int n) {
    for(int j = 1 ; j < n ; j *= 10) {
        for(int i = 0 ; i < n ; ++ i) {
            if((i / j) % 10) {
                (f[i - j] -= f[i]) %= mod;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    pw[0] = 1;
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        cnt[x] ++;
        (sig[x] += x) %= mod;
        (sig2[x] += (ll) x * x % mod) %= mod;
        pw[i] = pw[i - 1] * 2 % mod;
    }
    fmt(1000000);
    for(int i = 0 ; i < 1000000 ; ++ i) {
        if(!cnt[i]) {
            continue;
        } else if(cnt[i] == 1) {
            f[i] = sig2[i];
        } else {
            f[i] = pw[cnt[i] - 2] * (sig[i] * sig[i] % mod + sig2[i]) % mod;
        }
    }
    invfmt(1000000);
    ll ans = 0;
    for(int i = 0 ; i < 1000000 ; ++ i) {
        ans ^= (ll) i * ((f[i] % mod + mod) % mod);
    }
    printf("%lld\n", ans);
}
