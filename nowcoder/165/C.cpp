#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, mod = 1e4 + 7;
 
int n, a[N];
 
ll pw(ll n) { return n * n % mod; }
 
ll min3(ll a, ll b, ll c) { return min(a, min(b, c)); }
 
ll min4(ll a, ll b, ll c, ll d) { return min(min(a, b), min(c, d)); }
 
namespace allsame {
    bool check() {
        for(int i = 1 ; i <= n ; ++ i) if(a[i] != a[1]) return 0;
        return 1;
    }
    ll pw(ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod)
            if(b & 1)
                r = r * a % mod;
        return r;
    }
    void sol() {
        ll c = a[1] - 1;
        ll T = pw(c, n);
        if(n & 1) T -= c;
        else T += c;
        T = (T % mod + mod) % mod;
        printf("%lld\n", T);
    }
}
 
namespace n4 {
    bool check() {
        return n <= 4;
    }
    void sol() {
         
        if(n == 1) {
            printf("%d\n", a[1]);
        } else if(n == 2) {
            ll T = (1ll * a[1] * a[2] % mod - min(a[1], a[2])) % mod;
            T = (T % mod + mod) % mod;
            printf("%lld\n", T);
        } else if(n == 3) {
            ll T = 1ll * a[1] * a[2] % mod * a[3] % mod;
             
            (T -= 1ll * min(a[1], a[2]) * a[3] % mod) %= mod;
            (T -= 1ll * min(a[1], a[3]) * a[2] % mod) %= mod;
            (T -= 1ll * min(a[2], a[3]) * a[1] % mod) %= mod;
             
            (T += min3(a[1], a[2], a[3]) * 2) %= mod;
             
            T = (T % mod + mod) % mod;
            printf("%lld\n", T);
        } else if(n == 4) {
             
            ll F1, F2, F3, F4;
             
            F1 = 1, F2 = -1, F3 = 1, F4 = -1;
             
            ll T = 1ll * a[1] * a[2] % mod * a[3] % mod * a[4] % mod * F1 % mod;
             
            (T += 1ll * min(a[1], a[2]) * a[3] % mod * a[4] % mod * F2 % mod) %= mod;
            (T += 1ll * min(a[2], a[3]) * a[1] % mod * a[4] % mod * F2 % mod) %= mod;
            (T += 1ll * min(a[3], a[4]) * a[1] % mod * a[2] % mod * F2 % mod) %= mod;
            (T += 1ll * min(a[4], a[1]) * a[2] % mod * a[3] % mod * F2 % mod) %= mod;
             
            (T += 1ll * min3(a[1], a[2], a[3]) * a[4] % mod * F3 % mod) %= mod;
            (T += 1ll * min3(a[2], a[3], a[4]) * a[1] % mod * F3 % mod) %= mod;
            (T += 1ll * min3(a[3], a[4], a[1]) * a[2] % mod * F3 % mod) %= mod;
            (T += 1ll * min3(a[4], a[1], a[2]) * a[3] % mod * F3 % mod) %= mod;
             
            (T += 1ll * min4(a[1], a[2], a[3], a[4]) % mod * F4 % mod * 3 % mod) %= mod;
             
            (T += 1ll * min(a[1], a[2]) * min(a[3], a[4]) % mod) %= mod;
            (T += 1ll * min(a[1], a[4]) * min(a[2], a[3]) % mod) %= mod;
             
            T = (T % mod + mod) % mod;
             
            printf("%lld\n", T);
        }
    }
}
 
namespace naa {
    bool check() {
        if(n > 100) return 0;
        for(int i = 1 ; i <= n ; ++ i)
            if(a[i] > 100)
                return 0;
        return 1;
    }
    ll f[2][110][110], g[2][110];
    void sol() {
        int p = 0;
        for(int i = 1 ; i <= a[1] ; ++ i) f[p][i][i] = 1;
        for(int i = 1 ; i <= a[1] ; ++ i)
            for(int j = 1 ; j <= a[1] ; ++ j)
                g[p][i] = (g[p][i] + f[p][i][j]) % mod;
        for(int i = 2 ; i <= n ; ++ i) {
            p ^= 1;
            memset(f[p], 0, sizeof f[p]);
            memset(g[p], 0, sizeof g[p]);
            for(int j = 1 ; j <= a[1] ; ++ j) {
                for(int k = 1 ; k <= a[i] ; ++ k) {
                    f[p][j][k] = g[p ^ 1][j];
                    if(k <= a[i - 1]) f[p][j][k] -= f[p ^ 1][j][k];
                    g[p][j] = (g[p][j] + f[p][j][k]) % mod;
                }
            }
        }
        ll ans = 0;
        for(int i = 1 ; i <= a[1] ; ++ i)
            for(int j = 1 ; j <= a[n] ; ++ j)
                if(i != j)
                    ans = (ans + f[p][i][j]) % mod;
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}
 
int main() {
    scanf("%d%d", &n, &a[1]);
    allsame :: sol(); exit(0);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    
    if(allsame :: check()) allsame :: sol();
    else if(naa :: check()) naa :: sol();
    else if(n4 :: check()) n4 :: sol();
    else allsame :: sol();
}
