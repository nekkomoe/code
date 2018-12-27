#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 998244353;

ll pw(ll a, ll b) {
    if(b < 0) return pw(pw(a, -b), mod - 2);
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll inv(ll a) {
    return pw(a, mod - 2);
}

ll n, c, d, b[N], pri[N], vis[N], tot;

// h = f * g
void convolution(ll *f, ll *g, ll *h, int n) {
    for(int i = 1 ; i <= n ; ++ i) h[i] = 0;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; i * j <= n ; ++ j)
            (h[i * j] += f[i] * g[j] % mod) %= mod;
}

ll tau[N], mu[N], hat_b[N], g[N], f[N], hat_h[N], f_r[N], x[N], h[N];

void output(string name, ll *f) {
    cout << name << ": ";
    for(int i = 1 ; i <= n ; ++ i) cout << (f[i] % mod + mod) % mod << ' ';
    cout << endl;
}

void sol() {
    for(int i = 1 ; i <= n ; ++ i) cin >> b[i];
    
    for(int i = 1 ; i <= n ; ++ i) hat_b[i] = b[i] * inv(g[i]) % mod;
    convolution(hat_b, mu, tau, n);
    
    for(int i = 1 ; i <= n ; ++ i) {
        if(!inv(f_r[i]) && tau[i]) {
            cout << -1 << endl;
            return ;
        }
        hat_h[i] = tau[i] * inv(f_r[i]) % mod;
    }
    
    for(int i = 0 ; i <= n ; ++ i) h[i] = 0;

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i ; j <= n ; j += i) {
            (h[i] += hat_h[j] * mu[j / i] % mod) %= mod;
        }
    }

    for(int i = 1 ; i <= n ; ++ i) x[i] = h[i] * inv(g[i]) % mod;
    
    for(int i = 1 ; i <= n ; ++ i) cout << (x[i] % mod + mod) % mod << ' '; cout << endl;
}


int main() {
//    freopen("data.in", "r", stdin);
    
    ios :: sync_with_stdio();
    int q; cin >> n >> c >> d >> q;
    
    // init mu
    mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        } 
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    } 
    
    
    // init f
    for(int i = 1 ; i <= n ; ++ i) f[i] = pw(i, c - d);
    
    // init f_r
    convolution(f, mu, f_r, n);
    
    // init g
    for(int i = 1 ; i <= n ; ++ i) g[i] = pw(i, d);
    
    while(q --) sol();
}

