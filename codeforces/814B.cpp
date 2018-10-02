#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, a[N], b[N], p[N];
bool check() {
    int tot = 0;
    for(int i = 1 ; i <= n ; ++ i)
        if(b[i] != p[i])
            ++ tot;
    return tot == 1;
}
int vis[N];
int main() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) cin >> a[i];
    for(int i = 1 ; i <= n ; ++ i) cin >> b[i];
    
    for(int i = 1 ; i <= n ; ++ i) {
        p[i] = a[i];
    }
    
    int pos1, pos2;
    for(int i = 1 ; i <= n ; ++ i) {
        if(vis[a[i]]) {
            pos1 = vis[a[i]], pos2 = i;
        } else {
            vis[a[i]] = i;
        }
    }
    for(int i = 1 ; i <= n ; ++ i)
        if(!vis[i]) {
            p[pos1] = i;
            if(check()) {
                break;
            } else {
                p[pos1] = p[pos2];
                p[pos2] = i;
            }
        }
    for(int i = 1 ; i <= n ; ++ i)
        printf("%d ", p[i]); puts("");
}