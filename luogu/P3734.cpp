// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll n, m, r;
int o;
ll f[70][70][70], C[70][70], ans[int(1e5)];

struct T {
    ll x, y, z;
} tmp[int(1e5)];
bool cmp(T a, T b) {
    return make_pair(make_pair(a.x, a.y), a.z) < make_pair(make_pair(b.x, b.y), b.z);
}

int main() {
    scanf("%lld%lld%lld%d", &n, &m, &r, &o);
    for(int i = 1 ; i <= o ; ++ i) {
        scanf("%lld%lld%lld", &tmp[i].x, &tmp[i].y, &tmp[i].z);
    }
    tmp[++ o] = (T) { n, m, r };
    C[0][0] = 1;
    for(int i = 1 ; i < 70 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j < 70 ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    f[0][0][0] = 1;
    for(int i = 0 ; i < 70 ; ++ i) {
        for(int j = 0 ; j < 70 ; ++ j) {
            for(int k = 0 ; k < 70 ; ++ k) {
                if(!i && !j && !k) continue;
                ll res = 0;
                for(int x = 1 ; x <= i ; ++ x) {
                    (res += f[i - x][j][k] * C[i][x] % mod) %= mod;
                }
                for(int x = 1 ; x <= j ; ++ x) {
                    (res += f[i][j - x][k] * C[j][x] % mod) %= mod;
                }
                for(int x = 1 ; x <= k ; ++ x) {
                    (res += f[i][j][k - x] * C[k][x] % mod) %= mod;
                }
                f[i][j][k] = res;
            }
        }
    }
    sort(tmp + 1, tmp + 1 + o, cmp);
    for(int i = 1 ; i <= o ; ++ i) {
        ll x = tmp[i].x, y = tmp[i].y, z = tmp[i].z;
        ans[i] = f[__builtin_popcountll(x)][__builtin_popcountll(y)][__builtin_popcountll(z)];
        for(int j = 1 ; j < i ; ++ j) {
            ll a = tmp[j].x, b = tmp[j].y, c = tmp[j].z;
            if((a & x) == a && (b & y) == b && (c & z) == c) {
                (ans[i] -= ans[j] * f[__builtin_popcountll(x ^ a)][__builtin_popcountll(y ^ b)][__builtin_popcountll(z ^ c)] % mod) %= mod;
            }
        }
    }
    printf("%lld\n", (ans[o] + mod) % mod);
}
