#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2010, mod = 1e9 + 7;

vector<int> val[N * N];

int n, m, a[N][N], b[N][N], rev[N * N];
int num[N * N], num_cnt;
ll pw[N];

int main() {
    scanf("%d%d", &m, &n);

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &a[i][j]);
            num[++ num_cnt] = a[i][j];
        }
    }
    sort(num + 1, num + 1 + num_cnt);
    num_cnt = unique(num + 1, num + 1 + num_cnt) - num - 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            b[i][j] = lower_bound(num + 1, num + 1 + num_cnt, a[i][j]) - num;
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            val[b[i][j]].push_back(i);
            rev[b[i][j]] = a[i][j];
        }
    }
    pw[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) pw[i] = pw[i - 1] * m % mod;
    ll ans = 0;
    for(int i = 1 ; i <= num_cnt ; ++ i) {
        ll tot = 1;
        int cnt = n;
        for(int j = 0 ; j < val[i].size() ; ) {
            int k = j;
            while(k + 1 < val[i].size() && val[i][k + 1] == val[i][j]) {
                ++ k;
            }
            tot = (tot * (m - (k - j + 1)) % mod) % mod;
            -- cnt;
            j = k + 1;
        }
        (ans += (pw[n] - tot * pw[cnt] % mod) * rev[i] % mod) %= mod;
    }
    printf("%lld\n", (ans + mod) % mod);
}
