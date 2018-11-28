#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2010;

ll A, n, mod;

ll x[N], y[N], f[N][N];

ll pw(ll a, ll b) {
    ll r = 1;
    a %= mod;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll sol(ll T, int n) {
    ll res = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        ll pro = 1;
        for(int j = 0 ; j <= n ; ++ j) {
            if(i != j) {
                pro = (T - x[j]) % mod * pro % mod;
                pro = pw(x[i] - x[j], mod - 2) * pro % mod;
            }
        }
        res = (res + y[i] * pro % mod) % mod;
    }
    return res;
}

int main() {
    cin >> A >> n >> mod;
    for(int i = 0 ; i <= 2 * n ; ++ i) f[i][0] = 1;
    for(int i = 1 ; i <= 2 * n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            f[i][j] = (f[i - 1][j - 1] * i % mod * j % mod + f[i - 1][j]) % mod;
        }
    }
    for(int i = 0 ; i <= 2 * n ; ++ i) {
        x[i] = i;
        y[i] = f[i][n];
    }
    if(A <= 2 * n) cout << f[A][n] << endl;
    else cout << (sol(A, 2 * n) + mod) % mod << endl;
}

