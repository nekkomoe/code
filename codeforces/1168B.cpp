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

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

ll ans;
char str[int(3e5) + 10];

int main() {
    scanf("%s", str + 1);
    int n = strlen(str + 1);
    int mxr = n + 10;
    for(int i = n ; i >= 1 ; -- i) {
        for(int j = 1 ; i + 2 * j <= n ; ++ j) {
            if(str[i] == str[i + j] && str[i] == str[i + 2 * j]) {
                mxr = min(mxr, i + 2 * j);
                break;
            }
        }
        ans += max(0, n - mxr + 1);
    }
    printf("%lld\n", ans);
}
