#include "bits/stdc++.h"
using namespace std;
int n, k, vis[30];
char s[60];
int cnt, ans;
void dfs(int i) {
    // cout << char('a' + i) << endl;
    if(cnt == k) return ;
    ++ cnt;
    ans += i + 1;
    for(int j = i + 2 ; j < 26 ; ++ j) {
        if(vis[j]) {
            dfs(j);
            break;
        }
    }
}
int main() {
    scanf("%d%d%s", &n, &k, s + 1);
    for(int i = 1 ; i <= n ; ++ i) vis[s[i] - 'a'] = 1;
    for(int i = 0 ; i < 26 ; ++ i)
        if(vis[i]) {
            dfs(i);
            break;
        }
    if(cnt < k) puts("-1");
    else {
        printf("%d\n", ans);
    }
}
