// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010, FAFA = 1e5 + 10, mod = 998244353;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)   
            r = r * a % mod;
    return r;
}

int n, k, m, ans;

ll p[N], f[2][10010][20];

int main() {
    ios :: sync_with_stdio(0);
    
    cin >> n >> k >> m;
    for(int i = 1 ; i <= n ; ++ i) cin >> p[i];
    k = n - k + 1;
    
    int cur = 0;
    for(int j = 1 ; j <= k ; ++ j) f[cur][0][j] = -1;
    
    for(int i = 1 ; i <= n ; ++ i) {
        cur ^= 1;
        memset(f[cur], 0, sizeof f[cur]);
        for(int j = 0 ; j <= m ; ++ j) {
            for(int k = 1 ; k <= :: k ; ++ k) {
                f[cur][j][k] = f[cur ^ 1][j][k];
                if(j >= p[i]) {
                    f[cur][j][k] = (f[cur][j][k] + f[cur ^ 1][j - p[i]][k - 1] - f[cur ^ 1][j - p[i]][k]) % mod;
                }
            }
        }
    }
    
    for(int i = 1 ; i <= m ; ++ i) {
        ans += m * pw(i, mod - 2) % mod * f[cur][i][k] % mod;
        ans %= mod;
    }
    
    cout << (ans % mod + mod) % mod << endl;
}

