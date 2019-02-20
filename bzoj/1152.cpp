#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 10000, base = 147, MOD = 998244353;
ll hs[N], pw[N], sigpw[N];
int str[N];
ll get(int l, int r) {
    return ((hs[r] - hs[l - 1] * pw[r - l + 1] % MOD) % MOD + 0) % MOD;
}

void runprog() {
    int m; scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) scanf("%d", &str[i]);
    for(int i = 1 ; i <= m ; ++ i) hs[i] = (hs[i - 1] * base % MOD + str[i]) % MOD;
    int ans = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        // cout << get(1, i) << ' ' << get(m - i + 1, m) << endl;
        if(get(1, i) == get(m - i + 1, m)) {
            ans = (ans + sigpw[i]) % mod;
            // cout << i << endl;
        }
    }
    printf("%04d\n", ans);
}

int main() {
    int sig, t; scanf("%d%d", &sig, &t);
    pw[0] = sigpw[0] = 1;
    for(int i = 1 ; i <= int(1e5) ; ++ i) {
        pw[i] = pw[i - 1] * base % MOD;
        sigpw[i] = sigpw[i - 1] * sig % mod;
    }
    while(t --) {
        runprog();
    }
}

