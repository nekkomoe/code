#include "bits/stdc++.h"
using namespace std;

class BearPermutations2 {
public:
    typedef long long ll;
    vector<vector<ll> > f, c;
    vector<ll> fac;
    int n, mod;
    ll pw(ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod) {
            if(b & 1) {
                r = r * a % mod;
            }
        }
        return r;
    }
    ll C(int n, int m) {
        return n < m || m < 0 ? 0 : c[n][m];
    }
    void chksum(ll &a, ll b) {
        a = (a + b) % mod;
    }
    ll S(ll l, ll r) {
        return (l + r) * (r - l + 1) / 2 % mod;
    }
    int getSum(int t_n, int t_mod) {
        n = t_n, mod = t_mod;
        ll res = 0;
        c = f = vector<vector<ll> > (n + 10, vector<ll> (n + 10));
        fac = vector<ll> (n + 10);
        
        fac[0] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            fac[i] = fac[i - 1] * i % mod;
        }
        c[0][0] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            c[i][0] = 1;
            for(int j = 1 ; j <= i ; ++ j) {
                c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
            }
        }
        for(int i = n ; i >= 1 ; -- i) {
            for(int j = i ; j <= n ; ++ j) {
                for(int k = i ; k <= j ; ++ k) {
                    if(k > i) {
                        chksum(f[i][j], C(j - i, k - i) * f[i][k - 1] % mod * fac[j - k] % mod);
                    }
                    if(k < j) {
                        chksum(f[i][j], C(j - i, k - i) * f[k + 1][j] % mod * fac[k - i] % mod);
                    }
                    if(i < k && k < j) {
                        chksum(f[i][j],
                            (fac[k - i - 1] * fac[j - k - 1] % mod * C(j - i, k - i) % mod)
                            * (S(k + 1, j) * (k - i) % mod - S(i, k - 1) * (j - k) % mod) % mod
                        );
                    }
                }
            }
        }
        
        res = f[1][n];
        return int((res % mod + mod) % mod);
    }
};

// int main() {
//     int n, mod;
//     scanf("%d%d", &n, &mod);
//     printf("%d\n", (new BearPermutations2) -> getSum(n, mod));
// }
