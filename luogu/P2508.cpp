// luogu-judger-enable-o2
#include <cmath>
#include <cstdio>
 
typedef long long lnt;
 
lnt r, ans;
 
inline lnt gcd(lnt a, lnt b) {
    for (lnt c; b; )
        c = a % b, a = b, b = c;
     
    return a;
}
 
signed main() {
    scanf("%lld", &r), r <<= 1;
     
    for (lnt d = 1, t; d * d <= r; ++d)
        if (r % d == 0) {
            t = r / d;
             
            for (lnt u = 1; u * u <= t; ++u) {
                lnt v = sqrt(t - u * u) + 1E-5;
                 
                if (u >= v)continue;
                 
                if (v * v == t - u * u && gcd(u, v) == 1)
                    ++ans;
            }
             
            if (d * d == r)continue;
             
            t = d;
             
            for (lnt u = 1; u * u <= t; ++u) {
                lnt v = sqrt(t - u * u) + 1E-5;
                 
                if (u >= v)continue;
                 
                if (v * v == t - u * u && gcd(u, v) == 1)
                    ++ans;
            }
        }
     
    printf("%lld\n", (ans << 2) + 4);
}
