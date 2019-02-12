#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 3e5 + 10, mod = 1e9 + 7, LOW_COV = 0x1ff, HIGH_COV = 0x3fe00, lim = 1ll << 10;

int n, a[N];

ll f[1ll << 12][1ll << 12], ans;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    reverse(a + 1, a + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        ll cnt = 0;
        int x = a[i];
        int high_x = (x & HIGH_COV) >> 9, low_x = x & LOW_COV;
        for(int s = high_x ; ; s = (s - 1) & high_x) {
            cnt = (cnt + f[s][low_x]) % mod;
            if(!s) break;
        }
        for(int s = 0 ; s < lim ; ++ s) {
            if((s & low_x) == 0) {
                (f[high_x][low_x | s] += cnt + 1) %= mod;
            }
        }
        ans = (ans + cnt) % mod;
    }
    printf("%lld\n", ans);
}
