#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1010, mod = 1e9 + 7;
int n;
ll a[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2);
ll C[N][N];

int main() {
    scanf("%d", &n);

    C[0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= n ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }

    a[0] = 1, a[1] = 1;
    for(int n = 2 ; n <= :: n ; ++ n) {
        for(int i = 0 ; i <= n - 1 ; ++ i) {
            a[n] += (i % 2 == 0) * C[n - 1][i] * a[i] % mod * a[n - 1 - i] % mod;
            a[n] %= mod;
        }
    }

    printf("%lld\n", a[n]);
}
