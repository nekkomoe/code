#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    ll n, l;
    scanf("%lld%lld", &n, &l);
    ll ans = -1;

    // all xor = 1
    // [1, l]: xi=1
    // (l,n]: xi=0
    if(l % 2 == 1) {
        if(ans == -1 || l < ans) {
            ans = l;
        }
    }


    // all xor = 0
    // [1, l]: xi=0
    // (l, n]: xi=1
    l = n - l;
    if(l % 2 == 0) {
        if(ans == -1 || l < ans) {
            ans = l;
        }
    }

    if(ans == -1) puts("Impossible");
    else printf("%lld\n", ans);
}
