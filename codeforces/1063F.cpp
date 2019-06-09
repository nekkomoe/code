#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5e5 + 10, mod = 2333333, base = 137;

int n, ans = 1; char str[N];
bitset<mod + 10> vis;
bitset<N> f[1010];
int hs[N];

int main() {
    scanf("%d%s", &n, str + 1);

    for(int i = 1 ; i <= n ; ++ i) {
        f[1][i] = 1;
        hs[i] = str[i] - '0';
    }
    for(int i = 2 ; i <= 1000 ; ++ i) {
        vis = 0;
        for(int j = n - i + 1 ; j >= 1 ; -- j) {
            if(j + i <= n && f[i - 1][j + i]) {
                vis[hs[j + i]] = 1;
            }
            if(vis[hs[j]] || vis[hs[j + 1]]) {
                ans = i;
                f[i][j] = 1;
            }
        }
        for(int j = 1 ; j + i - 1 <= n ; ++ j) {
            hs[j] = ((ll) hs[j] * base + str[j + i - 1] - 'a') % mod;
        }
    }

    printf("%d\n", ans);
}
