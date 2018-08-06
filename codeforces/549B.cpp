#include "bits/stdc++.h"
using namespace std;
const int N = 110;
int n, a[N], vis[N];
char mp[N][N];
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%s", mp[i] + 1);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int k = 1 ; k <= n ; ++ k) {
        for(int i = 1 ; i <= n ; ++ i) {
            if(a[i] == 0) {
                vis[i] = 1;
                for(int j = 1 ; j <= n ; ++ j) {
                    if(mp[i][j] == '1') {
                        -- a[j];
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) ans += vis[i];
    printf("%d\n", ans);
    for(int i = 1 ; i <= n ; ++ i) if(vis[i]) printf("%d ", i);
    puts("");
}
