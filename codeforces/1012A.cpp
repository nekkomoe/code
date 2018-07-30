#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int a[N], n;
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= 2 * n ; ++ i) scanf("%d", &a[i]);
    sort(a + 1, a + 1 + 2 * n);
    ll ans = (ll) (a[n] - a[1]) * (a[2 * n] - a[n + 1]);
    ll x = a[2 * n] - a[1];
    for(int i = 2 ; i + n - 1 <= 2 * n - 1 ; ++ i) {
        ans = min(ans, x * (a[i + n - 1] - a[i]));
    }
    printf("%lld\n", ans);
}
