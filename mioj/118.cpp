#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int vis[N], pri[N], tot;

ll sum[N], phi[N];

ll sol(int n, int a) {
    ll res = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        sum[i] = (pw(a, i) + sum[i - 1]) % mod;
    }
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res += (phi[n / i] - 1) * (sum[j] - sum[i - 1]) % mod;
        res %= mod;
    } 
    return res;
}

int main() {
    ll n, a, b; cin >> n >> a >> b;
    phi[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            phi[i] = i - 1;
            pri[++ tot] = i;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            }
        }
        phi[i] = (phi[i] + phi[i - 1]) % mod;
    }
    ll ans = (sol(n, a) - sol(n, b)) % mod;
    int cnt = 0;
    for(int m = 0 ; m <= n ; ++ m) {
        if((n & m) == m) {
            ++ cnt;
        }
    }
    ans = ans * cnt % mod;
    cout << (ans + mod) % mod << endl;
}

