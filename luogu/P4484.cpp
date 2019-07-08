#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353;

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

int n;
int h[30]; // 某一行的长度
int a[30][30], dn[30][30], rig[30][30];

void dfs(int stp, int res) {
    if(res == 0) {
        memset(dn, 0, sizeof dn);
        memset(rig, 0, sizeof rig);
        for(int i = 1 ; i < stp ; ++ i) {
            for(int j = 1 ; j <= h[i] ; ++ j) {
                a[i][j] = 1;
            }
        }
        
        for(int i = stp - 1 ; i >= 1 ; -- i) {
            for(int j = 1 ; j <= h[i] ; ++ j) {
                if(a[i][j]) {
                    dn[i][j] = i;
                }
                dn[i][j] = max(dn[i][j], dn[i + 1][j]);
            }
        }

        ll pro = 1;
        for(int i = 1 ; i < stp ; ++ i) {
            for(int j = 1 ; j <= h[i] ; ++ j) {
                pro *= dn[i][j] - i + h[i] - j + 1;
                pro %= mod;
            }
        }

        // for(int i = 1 ; i < stp ; ++ i) {
        //     for(int j = 1 ; j <= h[i] ; ++ j) {
        //         printf("%d ", dn[i][j]);
        //     }
        //     puts("");
        // }

        

        ll fac = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            fac = fac * i % mod;
        }
        ll cnt = fac * getinv(pro) % mod;

        // for(int i = 1 ; i < stp ; ++ i) {
        //     for(int j = 1 ; j <= h[i] ; ++ j) {
        //         printf("%d ", a[i][j]);
        //     }
        //     puts("");
        // }
        // puts("");
        // printf("%lld, %d, %lld\n", cnt, h[1], pro);

        upd(ans, cnt * cnt % mod * h[1] % mod);
    } else {
        for(int i = 1 ; i <= h[stp - 1] && i <= res ; ++ i) {
            h[stp] = i;
            dfs(stp + 1, res - i);
        }
    }
}

int main() {
    scanf("%d", &n);
    h[0] = 0x3f3f3f3f;
    dfs(1, n);
    ll pro = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        pro = pro * i % mod;
    }
    // printf("ans = %lld\n", ans);
    ans = ans * getinv(pro) % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
}
