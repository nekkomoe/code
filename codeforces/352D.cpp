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

int n, a[N];

int main() {
    cin >> n;
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i];
        for(int j = 1 ; j < i ; ++ j) {
            if(a[j] > a[i]) {
                ++ ans;
            }
        }
    }
    if(ans & 1) printf("%d\n", 2 * ans - 1);
    else printf("%d\n", 2 * ans);
}
