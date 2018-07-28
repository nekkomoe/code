#include "bits/stdc++.h"
using namespace std;
const int N = 1010;
int n, ans = 0x3f3f3f3f, vis[N];
struct T { int w, h; } a[N];
bool operator < (T a, T b) { return a.w - a.h > b.w - b.h; }
void upd(int h) {
    for(int i = 1 ; i <= n ; ++ i) vis[i] = 0;
    int cnt = 0, sum = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i].h > h) {
            vis[i] = 1;
            sum += a[i].h;
            ++ cnt;
            if(a[i].w > h) return ;
        }
    }
    if(cnt > n / 2) return ;
    for(int i = 1 ; i <= n ; ++ i) {
        if(!vis[i]) {
            if(a[i].w > h || cnt + 1 > n / 2 || a[i].w < a[i].h) {
                sum += a[i].w;
            } else {
                ++ cnt;
                sum += a[i].h;
            }
        }
    }
    ans = min(ans, sum * h);
}
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &a[i].w, &a[i].h);
    sort(a + 1, a + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        upd(a[i].h);
        upd(a[i].w);
    }
    printf("%d\n", ans);
}
