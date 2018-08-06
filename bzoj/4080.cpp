#include <bits/stdc++.h>

using namespace std;

const int N = 110;

struct P {
    int x, y;
} p[N];

int n, d, id[N];

long long pw(long long x) { return x * x; }

int check(int i, int j) {
    return pw(p[i].x - p[j].x) + pw(p[i].y - p[j].y) <= pw(d);
}

int ans, as[N], vis[N], la[N], a[N][N];

int main() {
    
    srand((unsigned long long) new char);
    
    scanf("%d%d", &n, &d);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &p[i].x, &p[i].y), id[i] = i;
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            a[i][j] = check(i, j);
        }
    }
    
    for(int i = 1 ; i <= 1000 ; ++ i) {
        random_shuffle(id + 1, id + 1 + n);
        int res = 0;
        memset(vis, 0, sizeof vis), memset(la, 0, sizeof la);
        for(int i = 1 ; i <= n ; ++ i) {
            if(!vis[id[i]]) {
                vis[id[i]] = la[id[i]] = 1, ++ res;
                for(int j = i + 1 ; j <= n ; ++ j) {
                    if(!a[id[i]][id[j]]) vis[id[j]] = 1; 
                }
            }
        }
        if(res > ans) {
            ans = res;
            memcpy(as, la, sizeof la);
        }
    }
    
    printf("%d\n", ans);
    
    for(int i = 1 ; i <= n ; ++ i) if(as[i]) printf("%d ", i);
    
}
