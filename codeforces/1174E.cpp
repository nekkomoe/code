#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e6 + 10;

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

ll f[2][22][2];
ll n, p;
int calc(int x) {
    return n / x;
}

int main() {
    cin >> n;
    int k = log2(n);
    f[p][k][0] = 1;
    -- k;
    if(k >= 0 && (1 << k) * 3 <= n) {
        f[p][k][1] = 1;
    }
    for(int i = 2 ; i <= n ; ++ i) {
        p ^= 1;
        memset(f[p], 0, sizeof f[p]);
        for(int x = 0 ; x <= 20 ; ++ x) {
            upd(f[p][x][0], f[!p][x][0] * (calc(1 << x) - (i - 1)) % mod);
            upd(f[p][x][0], f[!p][x + 1][0] * (calc(1 << x) - calc(1 << (x + 1))) % mod);
            upd(f[p][x][0], f[!p][x][1] * (calc(1 << x) - calc((1 << x) * 3)) % mod);
            upd(f[p][x][1], f[!p][x][1] * (calc((1 << x) * 3) - (i - 1)) % mod);
            upd(f[p][x][1], f[!p][x + 1][1] * (calc((1 << x) * 3) - calc((1 << (x + 1)) * 3)) % mod);
        }
    }

    ll ans = f[p][0][0];
    cout << (ans % mod + mod) % mod << endl;            
}
