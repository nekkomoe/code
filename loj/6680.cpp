#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    // ---------------------------------------DECLARE--------------------------------------
    const int mod = 998244353;

    auto pw = [&] (ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod) {
            if(b & 1) {
                r = r * a % mod;
            }
        }
        return r;
    };

    auto getinv = [&] (ll n) {
        return pw(n, mod - 2);
    };

    auto upd = [&] (ll &a, ll b) {
        a = (a + b) % mod;
    };

    auto get_fac_invfac = [&] (int n) {
        vector<int> fac(n + 5), invfac(n + 5);
        fac[0] = invfac[0] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            fac[i] = (ll) fac[i - 1] * i % mod;
        }
        invfac[n] = getinv(fac[n]);
        for(int i = n - 1 ; i >= 1 ; -- i) {
            invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
        }
        return make_pair(fac, invfac);
    };

    auto C = [&] (int n, int m) {
        const int MXN = 1e5;
        static vector<int> fac, invfac;
        static int flag = ([&] () {
            auto tmp = get_fac_invfac(MXN + 5);
            fac = tmp.first, invfac = tmp.second;
            return 0;
        }) ();
        return n < m || m < 0 ? 0 : (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    };

    // ----------------------------------------BEGIN---------------------------------------
    
    int n; scanf("%d", &n);
    vector<int> vis(n + 5), pri, g1(n + 5), g2(n + 5), f(n + 5), sig(n + 5);
    g1[1] = sig[1] = g2[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            sig[i] = i;
            for(int p = 1, q = 1, lim = n / i ; p <= lim ; p *= i, ++ q) {
                sig[p * i] = p * i;
                g1[p * i] = ((ll) i * g1[p] % mod + (i ^ q)) % mod;
                g2[p * i] = ((ll) g2[p] + (i ^ q)) % mod;
            }
            pri.emplace_back(i);
        }
        for(int p: pri) {
            if(i * p > n) {
                break;
            }
            vis[i * p] = 1;
            if(i % p) {
                sig[i * p] = p;
                g1[i * p] = (ll) g1[i] * g1[p] % mod;
                g2[i * p] = (ll) g2[i] * g2[p] % mod;
            } else {
                sig[i * p] = sig[i] * p;
                int nek = i / sig[i], pro = sig[i] * p;
                g1[i * p] = (ll) g1[nek] * g1[pro] % mod;
                g2[i * p] = (ll) g2[nek] * g2[pro] % mod;
                break;
            }
        }
    }

    f[1] = 1;
    ll ans = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        f[i] = (f[i - 1] + ((ll) 2 * g1[i] - g2[i]) % mod) % mod;
        ans ^= f[i] < 0 ? f[i] + mod : f[i];
    }
    printf("%lld\n", ans);
    
    // -----------------------------------------END----------------------------------------

    return 0;
}
