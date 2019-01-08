#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
ll n, k, inv[int(1e5)];

int main() {
	ios :: sync_with_stdio(0);
    cin >> n >> k;
    for(int i = 1 ; i <= k + 10 ; ++ i) {
        inv[i] = pw(i, mod - 2);
    }
    vector<pair<int, int> > pri;
    for(ll i = 2 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            int cnt = 0;
            while(n % i == 0) {
                n /= i;
                ++ cnt;
            }
            pri.push_back({ i % mod, cnt });
        }
    }
    if(n > 1) {
        pri.push_back({ n % mod, 1 });
    }
    ll ans = 1;
    for(auto PRI: pri) {
        int val = PRI.first, cnt = PRI.second;
        vector<vector<ll> > f(k + 1, vector<ll> (cnt + 10, 0));
        f[0][cnt] = 1;
        for(int i = 1 ; i <= k ; ++ i) {
            for(int j = 0 ; j <= cnt ; ++ j) {
                for(int t = 0 ; t <= j ; ++ t) {
                    f[i][t] = (f[i][t] + f[i - 1][j] * inv[j + 1] % mod) % mod;
                }
            }
        }
        
        ll x = 1, sum = 0;
        for(int i = 0 ; i <= cnt ; ++ i) {
            sum = (sum + x * f[k][i] % mod) % mod;
            x = x * val % mod;
        }
        ans = ans * sum % mod;
    }
    cout << ans << endl;
}

