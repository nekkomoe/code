#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int main() {
    ios :: sync_with_stdio();
    int n; cin >> n;
    cout << 4 * pw(3, n - 1) % mod << endl;
    for(int i = 1 ; i <= n ; ++ i) {
        cout << "A 0 0 0 0" << endl;
    }
}

