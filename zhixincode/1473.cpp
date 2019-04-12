#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int n;
int check(int x, int y, int z) {
    return fabs(sqrt(x - sqrt(n * 4)) + sqrt(y) - sqrt(z)) < 1e-6;
}

void runprog() {
    scanf("%d", &n);
    int sqr = sqrt(n);
    if(n == 0 || sqr * sqr == n) {
        puts("infty");
    } else if(n % 4) {
        puts("0 0");
    } else {
        n /= 4;
        ll a = 0, b = 0;
        for(int y = 1 ; y * y <= n ; ++ y) {
            if(n % y == 0) {
                int z = n / y;
                int x = y + z;
                if(x >= 1 && check(x, y, z)) {
                    ++ a, b = (b + (ll) x * y % mod * z % mod) % mod;
                }
                if(n / y != y) {
                    int ty = y;
                    y = n / y;
                    z = n / y;
                    int x = y + z;
                    if(x >= 1 && check(x, y, z)) {
                        ++ a, b = (b + (ll) x * y % mod * z % mod) % mod;
                    }
                    y = ty;
                }
            }
        }
        printf("%lld %lld\n", a, b);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
