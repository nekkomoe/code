#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define FN "seqa"

const int N = 100010;

typedef long long ll;

int n, k;

ll a[N], ans;

bool check(ll m) {
    int blk = 0;
    ll tot = 0;
    for(int i = 1 ; i <= n ; i ++) {
        if(tot + a[i] > m) {
            blk ++;
            tot = a[i];
        } else {
            tot += a[i];
        }
    }
    if(tot) {
        blk ++;
        tot = 0;
    }
    return blk <= k;
}

int main() {
    freopen(FN ".in", "r", stdin);
    freopen(FN ".out", "w", stdout);
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%lld", &a[i]);
    }
    ll L = 0, R = 0x3f3f3f3f3f3f3f3f;
    while(L <= R) {
        ll M = (L + R) >> 1;
        if(check(M)) {
            ans = M;
            R = M - 1;
        } else {
            L = M + 1;
        }
    }
    printf("%lld\n", ans);
}
