#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e6 + 10, mod = 998244353;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
int n, a[N];
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
int pre_cnt[N], cnt[N];
ll f[N];

int main() {
    init(N - 1);
    scanf("%d", &n);
    int mx = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        ++ pre_cnt[a[i]];
        mx = max(mx, a[i]);
    }
    for(int i = 1 ; i <= mx ; ++ i) {
        for(int j = i ; j <= mx ; j += i) {
            cnt[i] += pre_cnt[j];
        }
    }
    for(int k = 1 ; k <= 7 ; ++ k) {
        for(int i = 1 ; i <= mx ; ++ i) {
            // printf("C(%d, %d) = %lld\n", cnt[i], k, C(cnt[i], k));
            f[i] = C(cnt[i], k);
        }
        for(int i = mx ; i ; -- i) {
            for(int j = i + i ; j <= mx ; j += i) {
                f[i] -= f[j];
                f[i] %= mod;
            }
            // printf("%lld ", f[i]);
        }
        // puts("");
        if(f[1]) {
            printf("%d\n", k);
            return 0;
        }
    }
    puts("-1");
}
