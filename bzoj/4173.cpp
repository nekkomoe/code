#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll calc(ll n) {
    ll res = n;
    for(ll i = 2 ; i * i <= n ; ++ i)
        if(n % i == 0) {
            res = res / i * (i - 1);
            while(n % i == 0) n /= i;
        }
    if(n > 1) res = res / n * (n - 1);
    return res % mod;
}

int main() {
    ll n, m; cin >> n >> m;
    cout << calc(n) * calc(m) % mod * (n % mod) % mod * (m % mod) % mod << endl;
}

