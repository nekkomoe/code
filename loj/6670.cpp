#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
const int mod = 998244353;

int n;
ll fac[N], invfac[N];
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}

int a[N];
int vis[N];

ll sol(int k) {
    if(k == n) return 0;
    int m = n / k;
    ll res = 0;
    
    for(int x = 1 ; 1 + (m - 1) * x <= n ; ++ x) {
        ll prod = 1;
        
//        for(int i = 1 ; i <= m ; ++ i) {
//            int cnt = 0;
//            if(i == m) {
//                cnt = n - (1 + (m - 1) * x);
//            } else {
//                cnt = x - 1;
//            }
//            prod = prod * (fac[cnt] * C(i * (k - x) + (x - 1), cnt) % mod) % mod;
//        }
        
        {
            // 计算 1 <= i < m
            for(int i = 1 ; i <= m - 1 ; ++ i) {
                prod = prod * fac[i * (k - x) + (x - 1)] % mod;
                prod = prod * invfac[i * (k - x)] % mod;
            }
        }
        
        {
            // 计算i == m
            int cnt = n - (1 + (m - 1) * x);
            prod = prod * (fac[cnt] * C(m * (k - x) + (x - 1), cnt) % mod) % mod;
        }
        
        res = (res + prod) % mod;
    }
    
    return res * pw(k, m) % mod;
}

ll f() {
    ll res = fac[n];
    for(int k = 1 ; k * k <= n ; ++ k) {
        if(n % k) continue;
        res = (res + sol(k)) % mod;
        if(k != n / k) {
            res = (res + sol(n / k)) % mod;
        }
    }
    return res;
}

int main() {
    init(N - 1);
    scanf("%d", &n);
    printf("%lld\n", f());
}
