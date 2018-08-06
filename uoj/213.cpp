#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, p = 998244353;

int n, a[N], h[N], sta[N], l[N], r[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &h[i]);
    h[0] = h[n + 1] = 0x3f3f3f3f;
    int tp = 0; sta[++ tp] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        while(h[sta[tp]] <= h[i]) -- tp;
        l[i] = sta[tp];
        sta[++ tp] = i;
    }
    sta[tp = 1] = n + 1;
    for(int i = n ; i ; -- i) {
        while(h[sta[tp]] < h[i]) -- tp;
        r[i] = sta[tp];
        sta[++ tp] = i;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int len = r[i] - l[i] - 1;
        int mn = min(i - l[i], r[i] - i);
        h[i] %= p;
        a[1] = (a[1] + h[i]) % p;
        a[mn + 1] = (a[mn + 1] - h[i]) % p;
        a[len - mn + 2] = (a[len - mn + 2] - h[i]) % p;
        a[len + 2] = (a[len + 2] + h[i]) % p;
    }
    int sum = 0;
    for(int i = 2 ; i <= n ; ++ i) a[i] = (a[i - 1] + a[i]) % p;
    for(int i = 2 ; i <= n ; ++ i) a[i] = ((a[i - 1] + a[i]) % p + p) % p;
    for(int i = 1 ; i <= n ; ++ i) sum ^= a[i];
    printf("%d\n", sum);
}
