#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10;
int n, m = 1, a[N]; ll cnt[N][21];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]), a[i] ^= a[i - 1];
        for(int j = 20 ; ~ j ; -- j) {
            cnt[i][j] = cnt[i - 1][j] + ((a[i] >> j) & 1);
        }
    }
    for(int i = 1, l, r ; i <= m ; ++ i) {
        l = 1, r = n;
        ll ans = 0;
        for(int j = 20 ; ~ j ; -- j) {
            ll x = cnt[r][j] - (l > 1 ? cnt[l - 2][j] : 0), y = r - l + 2 - x;
            ans += (x * y) << j;
        }
        printf("%lld\n", ans);
    }
}
