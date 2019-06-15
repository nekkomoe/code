#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

int n, a[110];

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        scanf("%d", &n);
        int mx = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%d", &a[i]);
        }
        mx = 3 * a[1];
        for(int i = 2 ; i <= n ; ++ i) {
            mx = max(mx, a[i] + 1);
        }
        if(mx & 1) ++ mx;
        printf("%d\n", mx);
    }
}
