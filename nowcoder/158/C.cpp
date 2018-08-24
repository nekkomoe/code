#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, m, a[N], s[N];
 
int pw(int a, int b) {
    int r = 1;
    for( ; b ; b >>= 1, a = 1ll * a * a % mod) if(b & 1) r = 1ll * r * a % mod;
    return r;
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), s[1] = (1ll * s[1] + a[i]) % mod;
    for(int i = 2 ; i <= int(1e5) + 1 ; ++ i) {
        s[i] = 1ll * (n - 1) * s[i - 1] % mod;
    }
    // for(int i = 0 ; i <= 5 ; ++ i) {
        // printf("s[%d] = %d\n", i, s[i]);
    // }
    while(m --) {
        int x, t;
        scanf("%d%d", &x, &t);
        int res = s[t + 1];
        int sig = t % 2 ? 1 : -1;
        // sig = -sig;
        int ans = ((1ll * res + sig * s[1]) * pw(n, mod - 2) % mod + (-sig) * a[x]) % mod;
        ans = (ans % mod + mod) % mod;
        printf("%d\n", ans);
    }
}
