#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 4010, mod = 1e9 + 7;
int n, k;
ll f[N], h[N];

struct Mat {
    int a[N];
    void init() {
        for(int i = 0 ; i <= 2 * k ; ++ i) {
            a[i] = 0;
        }
    }
    int& operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat res; res.init();
        for(int i = 0 ; i < k ; ++ i) {
            for(int j = 0 ; j < k ; ++ j) {
                (res[i + j] += (ll) a[i] * b[j] % mod) %= mod;
            }
        }
        for(int i = 2 * k - 2 ; i >= k ; -- i) {
            for(int j = 1 ; j <= k ; ++ j) {
                (res[i - j] += (ll) f[j] * res[i] % mod) %= mod;
            }
            res[i] = 0;
        }
        return res;
    }
} res, base;

int main() {
    scanf("%d%d", &n, &k);    
    for(int i = 1 ; i <= k ; ++ i) {
        scanf("%lld", &f[i]);
        f[i] = (f[i] % mod + mod) % mod;
    }
    for(int i = 0 ; i < k ; ++ i) {
        scanf("%lld", &h[i]);
        h[i] = (h[i] % mod + mod) % mod;
    }
    for(int i = k ; i <= 2 * k ; ++ i) {
        for(int j = 1 ; j <= k ; ++ j) {
            (h[i] += h[i - j] * f[j] % mod) %= mod;
        }
    }
    if(n <= 2 * k) {
        printf("%lld\n", (h[n] % mod + mod) % mod);
        return 0;
    }
    n -= k - 1;
    base[1] = res[0] = 1;
    for( ; n ; n >>= 1, base = base * base) {
        if(n & 1) {
            res = res * base;
        }
    }
    ll ans = 0;
    for(int i = 0 ; i < k ; ++ i) {
        (ans += res[i] * h[i + k - 1] % mod) %= mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}

/*
hack: https://www.lydsy.com/JudgeOnline/wttl/thread.php?tid=5340
*/
