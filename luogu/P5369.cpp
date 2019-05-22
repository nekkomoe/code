// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 21;
const int mod = 998244353;

ll f[1 << N], g[1 << N], sum[1 << N], ans, a[N];
int n;

int main() {

    scanf("%d", &n);
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%lld", &a[i]);
        f[1 << i] = 1;
    }
    int lim = (1 << n) - 1;
    for(int s = 1 ; s <= lim ; ++ s) {
        for(int i = 0 ; i < n ; ++ i) {
            if((s >> i) & 1) {
                sum[s] = sum[s ^ (1 << i)] + a[i];
                break;
            }
        }
    }

    g[0] = 1;

    for(int s = 1 ; s <= lim ; ++ s) {
        if(sum[s] > 0) {
            for(int i = 0 ; i < n ; ++ i) {
                if(!((s >> i) & 1)) {
                    (f[s ^ (1 << i)] += f[s]) %= mod;
                }
            }
        } else {
            for(int i = 0 ; i < n ; ++ i) {
                if((s >> i) & 1) {
                    (g[s] += g[s ^ (1 << i)]) %= mod;
                }
            }
        }
    }

    // for(int s = 1 ; s <= lim ; ++ s) {
    //     printf("%lld %lld %lld\n", f[s], g[s], sum[s]);
    // }

    for(int s = 1 ; s <= lim ; ++ s) {
        ans = (ans + f[s] * g[lim - s] % mod * (sum[s] % mod) % mod) % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
