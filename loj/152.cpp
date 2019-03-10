#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 5e6 + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
int n;
ll a[N], ppw[N], inv[N], prod[N];

int get() {
    int x = 0, c = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}

int main() {
    n = get();
    ppw[0] = prod[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = get();
        ppw[i] = ppw[i - 1] * 998244353 % mod;
        prod[i] = prod[i - 1] * a[i] % mod;
    }

    inv[n] = pw(prod[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        inv[i] = inv[i + 1] * a[i + 1] % mod;
    }
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ll val = inv[i] * prod[i - 1] % mod;
        ans = (ans + val * ppw[n - i] % mod) % mod;
    }
    printf("%lld\n", ans);
}
