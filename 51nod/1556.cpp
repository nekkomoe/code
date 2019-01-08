#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
} 

int n; ll m[N], f[N];

int main() {
	ios :: sync_with_stdio(0);
    cin >> n;
    m[0] = m[1] = 1;
    for(int i = 1 ; i < n ; ++ i) {
        m[i + 1] = ((2 * i + 3) % mod * m[i] % mod + 3 * i * m[i - 1] % mod) % mod * pw(i + 3, mod - 2) % mod;
    }
    f[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        f[i] = (3 * f[i - 1] % mod - m[i - 2]) % mod;
    }
    cout << (f[n] % mod + mod) % mod;
}

