#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const int N = 100010;

typedef long long ll;

int n;

ll d, a[N], ans;

int main() {
    scanf("%d%lld", &n, &d);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
    int l = 0, r = 0;
    a[0] = 0xcfcfcfcfcfcfcfcfll;
    for(int i = 1 ; i <= n ; ++ i) {
        // a[i] - d
        // a[i] - a[j] <= d
        // --> a[j] >= a[i] - d
        while(r + 1 < i && a[r + 1] < a[i] - d) ++ r;
        while(r + 1 < i && a[r + 1] >= a[i] - d) ++ r;
        while(l + 1 <= r && a[l] < a[i] - d) ++ l;
        // cout << l << ' ' << r << endl;
        if(l > 0 && r > 0 && l <= r && a[l] >= a[i] - d && a[r] >= a[i] - d) {
            ans += (
                    // l ~ r
                    (ll) (r - l + 1) * i - (ll) (l + r) * (r - l + 1) / 2 - (r - l + 1)
                   );
        }
    }
    printf("%lld\n", ans);
}

