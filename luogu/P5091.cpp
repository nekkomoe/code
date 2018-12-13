#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b, mod; 

ll getphi(ll n) {
    ll res = n;
    for(ll i = 2 ; i * i <= n ; ++ i)
        if(n % i == 0) {
            res = res / i * (i - 1);
            while(n % i == 0) n /= i;
        }
    if(n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}

ll pw(ll a, ll b) {
    ll res = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            res = res * a % mod;
    return res;
}

char str[int(2e7) + 10];

int main() {
    cin >> a >> mod;
    ll phi = getphi(mod);
    ll b = 0, f = 0;
    cin >> str + 1;
    for(int i = 1 ; str[i] ; ++ i) {
        char c = str[i];
        b = b * 10 + c - '0';
        if(b >= phi) {
            f = 1;
        }
        b %= phi;
    }
    if(f) b += phi;
    cout << pw(a, b) << endl;
} 

