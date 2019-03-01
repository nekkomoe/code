#include <bits/stdc++.h>
using namespace std;
const int N = (1ll << 20) + 10;
int n; typedef long long ll;
ll a[N], b[N], c[N];

void fwt(ll *f) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j + i / 2 < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                f[k] = u + v;
                f[k + i / 2] = u - v;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    int sum = 0, ans = n;
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        sum ^= x;
        c[x] = 1;
    }
    n = 1ll << 19;
    fwt(c);
    a[0] = 1;
    while(a[sum] == 0) {
        -- ans;
        fwt(a); for(int i = 0 ; i < n ; ++ i) b[i] = a[i] * c[i];
        fwt(b); for(int i = 0 ; i < n ; ++ i) a[i] = b[i] > 0;
    }
    printf("%d\n", ans);
}
