#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll a, b, c, mod, x, y;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
void eg(ll a, ll b, ll &x, ll &y) {
    if(!b) x = 1, y = 0;
    else eg(b, a % b, y, x), y -= a / b * x;
}
void sol() {
    scanf("%lld%lld%lld%lld", &mod, &a, &b, &c);
    if(mod == (mod & -mod)) {
        if(a > 1) {
            printf("%lld 1 1\n", mod / 2);
        } else if(b > 1) {
            printf("1 %lld 1\n", mod / 2);
        } else if(c > 1) {
            printf("%lld %lld %lld\n", mod / 2, mod / 2, mod / 2);
        } else {
            puts("1 1 2");
        }
    } else {
        eg(c, a * b, x, y), y = -y;
        while(x < 0 || y < 0) x += a * b, y += c;
        printf("%lld %lld %lld\n", pw(2, b * y), pw(2, a * y), pw(2, x));
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        sol();
    }
}
