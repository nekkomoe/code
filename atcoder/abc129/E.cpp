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
char s[N];
ll ans;
 
ll f(ll n) {
    return pw(3, n);
    ll r = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        r += pw(2, i) * C(n, i) % mod;
        r %= mod;
    }
    return r;
}
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}
 
int main() {
    init(N - 1);
 
    // for(int i = 1 ; i <= 10 ; ++ i) {
    //     cout << f(i) << endl;
    // }
    // exit(0);
 
    // for(int n = 0 ; n <= 100 ; ++ n) {
    //     int ans = 0;
    //     for(int a = 0 ; a <= n ; ++ a) {
    //         for(int b = 0 ; a + b <= n ; ++ b) {
    //             if((a + b) == (a ^ b)) {
    //                 assert((a & b) == 0);
    //                 ++ ans;
    //             }
    //         }
    //     }
    //     printf("%d, ", ans);
    // }
 
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int x = 0;
    upd(ans, f(n - 1));
    for(int i = 1 ; i <= n ; ++ i) {
        // lcp: [1, i - 1]
        // s[i]=0
        // rest: [i + 1, n]
        if(i > 1 && s[i] == '1') {
            int y = n - i;
            upd(ans, pw(2, x) * f(y) % mod);
        }
        x += s[i] == '1';
    }
    upd(ans, pw(2, x));
    printf("%lld\n", ans);
}
