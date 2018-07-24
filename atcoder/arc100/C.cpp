#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n;
ll a[N], ans;
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]), a[i] -= i;
    sort(a + 1, a + 1 + n);
    ll b = a[n / 2 + 1];
    for(int i = 1 ; i <= n ; ++ i) {
        ll t = a[i] - b;
        ans += t < 0 ? -t : t;
    }
    printf("%lld\n", ans);
}
