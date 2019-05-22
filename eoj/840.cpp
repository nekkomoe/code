#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1e8 + 7;

ll getsigma(ll n) {
    ll res = 0;
    for(ll i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            ++ res;
            if(n / i != i) {
               ++ res; 
            }
        }
    }
    return res % mod;
}

ll getphi(ll n) {
    ll res = n;
    for(ll i = 2 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            res -= res / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) {
        res -= res / n;
    }
    return res % mod;
}

int main() {
    ll n; cin >> n;
    ll ans = getsigma(n) * getphi(n) % mod;
    cout << ans << endl;
}
