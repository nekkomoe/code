#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int n, p, a[N], top, b[N], pos[N];
ll len[N];

ll getlen(ll x) {
    ll r = 1;
    while(x) {
        r *= 10;
        x /= 10;
    }
    return r;
}

int main() {
    scanf("%d%d", &n, &p);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &b[i]);
        pos[b[i]] = i;
        if(b[i] <= 25) {
            a[++ top] = b[i];
            len[top] = getlen(b[i]);
            // printf("%lld\n", getlen(b[i]));
        }
    }
    n = top;
    for(int s = 1 ; s < (1 << n) ; ++ s) {
        ll xor_sum = 0, sum = 0, tot = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            if((s >> (i - 1)) & 1) {
                xor_sum ^= a[i];
                sum = (sum * len[i] + a[i]) % p;
                ++ tot;
            }
        }
        if(xor_sum == 0 && sum == 0) {
            puts("Yes");
            printf("%lld\n", tot);
            for(int i = 1 ; i <= n ; ++ i) {
                if((s >> (i - 1)) & 1) {
                    printf("%d ", pos[a[i]]);
                }
            }
            return 0;
        }
    }
    puts("No");
}
