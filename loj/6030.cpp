#include "bits/stdc++.h"
typedef long long ll;
using namespace std;

const int N = 1010, inf = 0x3f3f3f3f;

int n, m, a[N][N], vis[N], ans = inf, whi[N];

char s[N][N];

int main() {
    int tag = inf;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s[i] + 1);
        for(int j = 1 ; j <= n ; ++ j) {
            a[i][j] = s[i][j] == '#';
            if(s[i][j] == '#') {
                vis[j] = 1;
                tag = 1;
            } else {
                whi[j] = 1;
            }
        }
    }
    int res = n;
    for(int i = 1 ; i <= n ; ++ i) res -= whi[i] == 0;
    for(int i = 1 ; i <= n ; ++ i) {
        int sum = 0;
        for(int j = 1 ; j <= n ; ++ j) {
            sum += a[i][j] == 0;
        }
        ans = min(ans, sum + res + (vis[i] ? 0 : tag));
    }
    printf("%d\n", ans == inf ? -1 : ans);
}
