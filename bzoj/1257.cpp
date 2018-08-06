#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    int n, k; scanf("%d%d", &n, &k);
    ll ans = (ll) n * k;
    for(int i = 1, j ; i <= n && k / i != 0 ; i = j + 1)
        j = min(n, k / (k / i)),
        ans -= (ll) (i + j) * (j - i + 1) / 2 * (k / i);
    printf("%lld\n", ans);
}
