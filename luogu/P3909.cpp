#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, mod = 1e9 + 7;

ll a[N], b[N], c[N];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        b[i] = c[i] = a[i];
    }
    for(int i = n ; i ; -- i) {
        c[i] = (c[i] + c[i + 1]) % mod;
        b[i] = (b[i] * c[i + 1] % mod + b[i + 1]) % mod;
        a[i] = (a[i] * b[i + 1] % mod + a[i + 1]) % mod;
    }
    printf("%lld\n", (6 * a[1] % mod + mod) % mod);
}

