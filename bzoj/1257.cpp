#include <cstdio>
long long n, k, ans, t, r;
 
int main() {
    scanf("%lld%lld", &n, &k);
    if(n > k) ans = k * (n - k), n = k;
    for(long long i = 1 ; i <= n ; i = r + 1) {
        t = k / i, r = k / t;
        if(r >= n) r = n;
        ans += (r - i + 1) * k - (i + r) * (r - i + 1) / 2 * t;
    }
    printf("%lld\n", ans);
}

