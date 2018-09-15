#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
 
using namespace std;
 
const int N = 50010;
 
int n, a[N], T, vis[N], b[N];
 
int main() {
    scanf("%d", &T);
    while(T --) {
        scanf("%d", &n);
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        sort(b + 1, b + 1 + n);
        int sz = unique(b + 1, b + 1 + n) - b - 1, f = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            int x = lower_bound(b + 1, b + 1 + sz, a[i]) - b;
            if(!vis[x]) {
                vis[x] = 1;
                if(!f) f = 1;
                else putchar(' ');
                printf("%d", a[i]);
            }
        }
        memset(vis, 0, sizeof(vis));
        puts("");
    }
}
