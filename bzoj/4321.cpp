#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;

const int mod = 7777777;

int n;

long long f[N];

int main() {
    scanf("%d", &n);
    f[1] = 1;
    f[4] = 2;
    f[5] = 14;
    for(int i = 6 ; i <= n ; ++ i) {
        f[i] =
    (i + 1) * f[i - 1] % mod
  - (i - 2) * f[i - 2] % mod
  - (i - 5) * f[i - 3] % mod
  + (i - 3) * f[i - 4] % mod;
        f[i] %= mod;
        f[i] += mod;
        f[i] %= mod;
    }
    printf("%lld\n", f[n]);
}

