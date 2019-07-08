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

ll a[N];

void runprog() {
    int n;
    ll s = 0;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%lld", &a[i]);
        s += a[i];
    }
    for(int i = 0 ; i < n ; ++ i) {
        ll avg = s - a[i];
        if(avg == (ll) (n - 1) * a[i]) {
            printf("%d\n", i + 1);
            return ;
        }
    }
    puts("Impossible");
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }    
}
