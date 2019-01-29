#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2010, mod = 998244353;
int n, m, a[N][N]; ll ans;
char str[N];

ll calc_ZhuDuiJiao() {
    ll res = 0;
    static ll sum[N][N];

    memset(sum, 0, sizeof sum);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            sum[i][j] = (sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]) % mod;
            if(a[i][j] == 1) {
                res = (res + (ll) sum[i - 1][j - 1] * (n - i + 1) % mod * (m - j + 1) % mod) % mod;
                sum[i][j] = (sum[i][j] + i * j) % mod;
            }
        }
    }

    return res * 2 % mod;
}

ll calc_Shu() {
    ll res = 0;
    static ll sum[N];
    for(int j = 1 ; j <= m ; ++ j) {
        memset(sum, 0, sizeof sum);
        for(int i = 1 ; i <= n ; ++ i) {
            sum[i] = sum[i - 1];
            if(a[i][j] == 1) {
                res += (ll) sum[i - 1] * (n - i + 1) % mod * (m - j + 1) % mod;
                res %= mod;
                sum[i] = (sum[i - 1] + i * j) % mod;
            }
        }
    }
    return res * 2 % mod;
}

ll calc_Heng() {
    ll res = 0;
    static ll sum[N];
    for(int i = 1 ; i <= n ; ++ i) {
        memset(sum, 0, sizeof sum);
        for(int j = 1 ; j <= m ; ++ j) {
            sum[j] = sum[j - 1];
            if(a[i][j] == 1) {
                res += (ll) sum[j - 1] * (n - i + 1) % mod * (m - j + 1) % mod;
                res %= mod;
                sum[j] = (sum[j - 1] + i * j) % mod;
            }
        }
    }
    return res * 2 % mod;
}

ll calc_Dian() {
    ll res = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(a[i][j] == 1) {
                res += (ll) i * j % mod * (n - i + 1) % mod * (m - j + 1) % mod;
                res %= mod;
            }
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str + 1);
        for(int j = 1 ; j <= m ; ++ j) {
            a[i][j] = str[j] - '0';
        }
    }

    ans = (ans + calc_Shu()) % mod;
    ans = (ans + calc_Heng()) % mod;
    ans = (ans + calc_Dian()) % mod;

    ans = (ans + calc_ZhuDuiJiao()) % mod;

    for(int i = 1 ; i <= n ; ++ i) {
        reverse(a[i] + 1, a[i] + 1 + m);
    }

    ans = (ans + calc_ZhuDuiJiao()) % mod;

    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
}

