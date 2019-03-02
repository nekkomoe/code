#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

int n, tot;
ll pri[N], cnt[N], ans;

void dfs(int stp, ll phi, ll s0, ll s1, ll prod) {
    if(stp == tot + 1) {
        (ans += prod * (prod - 1) % mod - phi * (s1 - s0) % mod) %= mod;
    } else {
        ll pw = 1, sum = 1, all = 1;
        for(int i = 1 ; i <= cnt[stp] ; ++ i) {
            all *= pri[stp];
        }
        for(int i = 0 ; i <= cnt[stp] ; ++ i) {
            dfs(stp + 1,
                i == cnt[stp] ? phi : phi * all / pw / pri[stp] * (pri[stp] - 1),
                s0 * (i + 1),
                s1 * sum,
                prod * pw
            );
            pw *= pri[stp];
            sum += pw;
        }
    }
}

void runprog() {
    ans = tot = 0;
    scanf("%d", &n);
    for(int i = 2 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            pri[++ tot] = i, cnt[tot] = 0;
            while(n % i == 0) {
                n /= i;
                ++ cnt[tot];
            }
        }
    }
    if(n > 1) {
        pri[++ tot] = n;
        cnt[tot] = 1;
    }
    dfs(1, 1, 1, 1, 1);
    printf("%lld\n", (ans + mod) % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
