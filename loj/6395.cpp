#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 3010, K = 20, mod = 59393;

ll n, k, a[N], g[N], f[N];

int main() {
    cin >> n >> k;
    for(ll i = 0 ; i <= k ; ++ i) {
        cin >> a[i];
    }
    if(n == 1) {
        printf("0 %lld\n", a[0]);
        return 0;
    }
    for(ll i = 1 ; i <= n ; ++ i) {
        ll x = 1;
        for(ll j = 0 ; j <= k ; ++ j) {
            g[i] = (g[i] + a[j] * x % mod) % mod;
            x = x * i % mod;
        }
        if(i > 1) {
            g[i] = (g[i] - g[1]) % mod;
        }
    }
    for(int i = 1 ; i <= n - 2 ; ++ i) {
        for(int j = i ; j <= n - 2 ; ++ j) {
            f[j] = max(f[j], f[j - i] + g[i + 1]);
        }
    }
    
    printf("%lld %lld\n", n - 1, f[n - 2] + n * g[1]);
    if(n == 2) {
        puts("1 2");
        return 0;
    }
    int x = n - 2, y = n, id = 0;
    while(x) {
        for(int i = 1 ; i <= x ; ++ i) {
            if(f[x - i] + g[i + 1] == f[x]) {
                x -= i;
                if(++ id != 1) printf("%d %d\n", id - 1, id);
                else ++ i;
                for(int j = 1 ; j < i ; ++ j) {
                    printf("%d %d\n", id, y --);
                }
                break;
            }
        }
    }
    printf("%d %d\n", id, id + 1);
}
