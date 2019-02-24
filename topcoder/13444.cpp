#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


class CountTables { 

public:
    ll s[5010][5010], g[5010];
    int howMany(int n, int m, int c) {
        int mod = 1e9 + 7;
        s[0][0] = 1;
        for(int i = 1 ; i <= 5000 ; ++ i) {
            for(int j = 1 ; j <= 5000 ; ++ j) {
                s[i][j] = ((i - 1) * s[i - 1][j] % mod + s[i - 1][j - 1]) % mod;
            }
        }
        ll ans = 0;
        g[0] = 1;
        for(int i = 1 ; i <= m ; ++ i) g[i] = g[i - 1] * c % mod;
        for(int i = 1 ; i <= m ; ++ i) {
            ll val = 1;
            for(int j = 1 ; j <= n ; ++ j) val = val * (g[i] - j + 1) % mod % mod;
            ans = (ans + ((m - i) & 1 ? -1 : 1) * s[m][i] * val % mod) % mod;
        }
        return (int) ((ans + mod) % mod);
    }
};
