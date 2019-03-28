#include "bits/stdc++.h"
using namespace std;
const int N = 5010, p = 998244353;
typedef long long ll;
int n, k, S[N][N];
int pw(int a, int b) {
    int r = 1;
    for( ; b ; b /= 2, a = 1ll * a * a % p) if(b & 1) r = 1ll * r * a % p;
    return r;
}
int main() {
    // freopen("songfenti.in", "r", stdin);
    // freopen("songfenti.out", "w", stdout);
    scanf("%d%d", &n, &k);
    S[0][0] = 1;
    for(int i = 1 ; i <= k ; ++ i) {
        for(int j = 1 ; j <= i ; ++ j) {
            S[i][j] = (S[i - 1][j - 1] + 1ll * j * S[i - 1][j] % p) % p;
        }
    }
    int ans = 0, tot = 1;
    for(int j = 0 ; j <= k ; ++ j) {
        ans = (ans + 1ll * S[k][j] * pw(2, n - j) % p * tot % p) % p;
        tot = 1ll * tot * (n - j) % p;
    }
    ans = (ll) ans * pw(n, p - 2) % p;
    printf("%lld\n", (1ll * ans % p + p) % p);
}
