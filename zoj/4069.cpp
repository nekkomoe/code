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

ll fac[N], invfac[N];
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
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

ll n, m;
const int inv2 = (mod + 1) / 2;
void runprog() {
    scanf("%lld%lld", &n, &m);
    if(n < m) {
        puts("0");
    } else if(n == m) {
        printf("%lld\n", fac[n - 1] * inv2 % mod);
    } else {
        ll res = 0;
        ll k = n - m;
        ll prod = 1;
        for(int i = m ; ~ i ; -- i) {
            res += C(k + i - 1, i) * C(k, m - i) % mod * prod % mod;
            res %= mod;
            prod = prod * -inv2 % mod;
        }
        res = res * fac[n] % mod * invfac[k] % mod;
        printf("%lld\n", (res % mod + mod) % mod);
    }
}

int main() {
    init(N - 1);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
