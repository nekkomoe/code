#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll pw(ll a, ll b) {
    if(b < 0) return pw(pw(a, -b), mod - 2); 
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll d, w, a[110], ans;

void geta() {
    static ll a[110][110];
    memset(a, 0, sizeof 0);
    int n = d + 2; ll x = 1;
    for(int i = 0 ; i <= n ; ++ i) {
        ll pro = 1, sum = 0;
        for(int j = 1 ; j <= x ; ++ j) sum = (sum + pw(j, d)) % mod;
        a[i][n] = sum;
        for(int j = 0 ; j <= d + 1 ; ++ j) {
            a[i][j] = pro;
            pro = pro * x % mod;
        }
        ++ x;
    }
    
    for(int i = 0 ; i <= n ; ++ i) {
        int ch = i;
        for(int j = i ; j <= n ; ++ j) {
            if(a[j][i]) {
                ch = j;
                break;
            }
        }
        for(int j = i ; j <= n ; ++ j) {
            swap(a[i][j], a[ch][j]);
        }
        for(int j = i + 1 ; j <= n ; ++ j) {
            ll w = a[j][i] * pw(a[i][i], mod - 2) % mod;
            for(int k = i ; k <= n ; ++ k) {
                (a[j][k] -= w * a[i][k] % mod) %= mod;
            }
        }
    }
    
    for(int i = n ; i >= 0 ; -- i) {
        a[i][n] = a[i][n] * pw(a[i][i], mod - 2) % mod;
        for(int j = i - 1 ; j >= 0 ; -- j) {
            (a[j][n] -= a[i][n] * a[j][i] % mod) %= mod;
        }
    }
    
    for(int i = 0 ; i <= d + 1 ; ++ i) {
        :: a[i] = a[i][n];
    }
}

const int N = 1e5 + 10;
ll p[N], A[N];

int main() {
    ios :: sync_with_stdio();
    cin >> d >> w;
    geta();
    for(int i = 1 ; i <= w ; ++ i) {
        cin >> p[i] >> A[i];
    }
    for(int i = 0 ; i <= d + 1 ; ++ i) {
        ll pro = 1;
        for(int j = 1 ; j <= w ; ++ j) {
            ll val = pw(p[j], A[j] * i) * (1 - pw(p[j], d - i)) % mod;
            pro = pro * val % mod;
        }
        ans += a[i] * pro % mod;
    }
    cout << (ans % mod + mod) % mod << endl;
}

