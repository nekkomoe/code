#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 210, mod = 1e9 + 7;

ll f[N][N], s[N][N];
int a[N], n;
char M[N][N];

void runprog() {
    scanf("%d", &n);
    memset(f, 0, sizeof f), memset(s, 0, sizeof s);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%s", M[i] + 1);
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            for(int k = 1 ; k <= n ; ++ k) {
                s[j][k] = M[a[j]][a[i]] == '1' ? f[j][k] : 0;
                (s[j][k] += s[j - 1][k] + s[j][k - 1] - s[j - 1][k - 1]) %= mod;
            }
        }
        for(int j = 1 ; j <= n ; ++ j) {
            for(int k = 1 ; k <= n ; ++ k) {
                if(a[i] == a[j] && a[i] == a[k]) {
                    (ans += s[j - 1][k - 1] + 1) %= mod;
                    (f[j][k] += s[j - 1][k - 1] + 1) %= mod;
                }
            }
        }
    }
    printf("%lld\n", (ans + mod) % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
