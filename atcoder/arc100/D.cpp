#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n;
ll a[N], s[N], ans;
ll calc(ll a, ll b, ll c, ll d) {
    return max(max(a, b), max(c, d)) - min(min(a, b), min(c, d));
}
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i];
    ans = calc(a[1], a[2], a[3], s[n] - s[3]);
    for(int i = 2, j = 1, k = 3 ; i <= n - 2 ; ++ i) {
        // [1, i]                   [i + 1, n]
        // [1, j] [j + 1, i]        [i + 1, k] [k + 1, n]
        while(j + 1 <= i && s[j + 1] <= s[i] - s[j + 1]) ++ j;
        while(k + 1 <= n && s[k + 1] - s[i] <= s[n] - s[k + 1]) ++ k;
        ll a = s[j], b = s[i] - s[j], c = s[k] - s[i], d = s[n] - s[k];
        ll tmp = calc(a, b, c, d);
        ll L = tmp, R = tmp;
        if(j + 1 <= i) L = min(L, calc(a + :: a[j + 1], b - :: a[j + 1], c, d));
        if(k + 1 <= n) R = min(R, calc(a, b, c + :: a[k + 1], d - :: a[k + 1]));
        if(j + 1 <= i && k + 1 <= n) ans = min(ans, calc(a + :: a[j + 1], b - :: a[j + 1], c + :: a[k + 1], d - :: a[k + 1]));
        ans = min(ans, min(L, R));
    }
    printf("%lld\n", ans);
}
