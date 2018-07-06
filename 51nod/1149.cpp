#include "bits/stdc++.h"
using namespace std;
typedef long double ld;
typedef long long ll;
const ld pi = acos(-1);
const int N = 1e6 + 10, mod = 1e9 + 7;
int n, fac[N], invfac[N], p[N];
int C(int n, int m) { return n < m ? 0 : (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod; }
int pw(int a, int b) {
    int r = 1;
    for( ; b ; b >>= 1, a = (ll) a * a % mod) if(b & 1) r = (ll) r * a % mod;
    return r;
}
int main() {
    scanf("%d", &n);
    if(n <= 3) puts("1");
    else {
        invfac[0] = fac[0] = 1;
        for(int i = 1 ; i <= n ; ++ i)
            p[i] = int((i - 4) / pi) + 1,
            fac[i] = (ll) fac[i - 1] * i % mod,
            invfac[i] = pw(fac[i], mod - 2);
        int ans = 0;
        for(int i = n ; i >= 3 ; -- i) {
            int s = n - i, t = p[i] - (p[i + 1] <= p[i]);
            ans = ((ll) ans + C(s + t, s)) % mod;
        }
        printf("%d\n", ans);
    }
}
