%:pragma GCC optimize(2)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 999911659;

ll pw(ll a, ll b, ll mod) { 
    ll res = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            res = res * a % mod;
    return a == 0 ? 0 : res;
}

const int pmod[4] = {
    2, 3, 4679, 35617
};

ll fac[40000], invfac[40000];

void get(int mod) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i < mod ; ++ i) fac[i] = fac[i - 1] * i % mod;
//    invfac[mod - 1] = pw(fac[mod - 1], mod - 2, mod);
//    for(int i = mod - 2 ; i >= 1 ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

ll C(ll n, ll m, ll mod) {
    if(n < m) return 0;
//    if(n < mod) return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    if(n < mod) return fac[n] * pw(fac[m], mod - 2, mod) % mod * pw(fac[n - m], mod - 2, mod) % mod;
    return C(n / mod, m / mod, mod) * C(n % mod, m % mod, mod) % mod;
}

ll val[4], n, g;

const ll poi[4][2] = {
    {499955829, 1},
    {333303886, 1},
    {213702, 1353},
    {28074, 31254}
};

ll CRT() {
    ll res = 0, mod = :: mod - 1;
    for(int i = 0 ; i < 4 ; ++ i) {
        res = (res + val[i] * poi[i][0] % mod * poi[i][1] % mod) % mod;
    }
    return res;
}

void sol(int d) {
    for(int j = 0 ; j < 4 ; ++ j) {
        get(pmod[j]);
        val[j] = (val[j] + C(n, d, pmod[j])) % pmod[j];
    }
}

int main() {
    
    cin >> n >> g;
    for(int i = 1 ; i * i <= n ; ++ i)
        if(n % i == 0) {
            sol(i);
            if(n / i != i) sol(n / i);
        }
    cout << pw(g, CRT() % mod, mod) << endl;
} 

