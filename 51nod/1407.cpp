#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = (1 << 21) + 10, mod = 1e9 + 7;

int n, len, a[N]; ll f[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int main() {
    scanf("%d", &len), n = 20;
    for(int i = 0 ; i < len ; ++ i) scanf("%d", &a[i]), ++ f[a[i]];
    for(int i = 0 ; i < n ; ++ i)
        for(int j = 0 ; j < (1 << n) ; ++ j)
//         for(int j = (1 << n) - 1 ; ~ j ; -- j)
            if(!((j >> i) & 1))
                f[j] = (f[j] + f[j ^ (1 << i)]) % mod;
    for(int i = 0 ; i < (1 << n) ; ++ i) f[i] = pw(2, f[i]) - 1;
    ll ans = 0;
    for(int i = 0 ; i < (1 << n) ; ++ i) {
        int cnt = 0;
        for(int j = 0 ; j < n ; ++ j) cnt += (i >> j) & 1;
        ans = (ans + (cnt & 1 ? -1 : 1) * f[i]) % mod;
    }
    if(ans < 0) ans += mod;
    
//    for(int i = 0 ; i < n ; ++ i)
////        for(int j = 0 ; j < (1 << n) ; ++ j)
//        for(int j = (1 << n) - 1 ; ~ j ; -- j)
//            if(!((j >> i) & 1))
//                f[j] = (f[j] - f[j ^ (1 << i)]) % mod;
//    ans = (f[0] + mod) % mod; 
    printf("%lld\n", ans);
}
