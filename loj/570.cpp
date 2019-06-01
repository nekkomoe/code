#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 1 << 23;
int n, m, k;

ll a[N];

void fwt(ll *f, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) {
                    f[k] = (u + v) % mod;
                    f[k + i / 2] = v;
                } else {
                    f[k] = (u - v) % mod;
                    f[k + i / 2] = v;
                }
            }
        }
    }
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    n = 1 << n;
    for(int i = 1, x ; i <= m ; ++ i) {
        scanf("%d", &x);
        a[x] ++;
    }
    fwt(a, 0);
    for(int i = 0 ; i < n ; ++ i) {
        a[i] = pw(a[i], k);
    }
    fwt(a, 1);
    ll ans = 0;
    for(int i = 1 ; i < n ; ++ i) {
        ans = (ans + a[i]) % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
