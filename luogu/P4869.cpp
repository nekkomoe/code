#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 10086;

ll a[100], pw = 1;
int n, x;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        for(int j = 31 ; ~ j ; -- j) {
            if(x & (1 << j)) {
                if(!a[j]) {
                    a[j] = x;
                    break;
                }
                x ^= a[j];
                if(!x) {
                    pw = pw * 2 % mod;
                    break;
                }
            }
        }
    }
    scanf("%d", &x);
    ll ans = 0, prod = 1;
    for(int i = 0 ; i <= 31 ; ++ i) {
        if(a[i]) {
            if(x & (1 << i)) {
                ans = (ans + prod) % mod;
            }
            prod = prod * 2 % mod;
        }
    }
    printf("%lld\n", (ans * pw + 1) % mod);
}
