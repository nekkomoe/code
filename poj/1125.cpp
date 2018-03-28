//floyd

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int N = 300;

int dis[N][N], n;

int main() {
    while(scanf("%d", &n) == 1 && n) {
        memset(dis, 0x3f, sizeof(dis));
        for(int i = 1, x, y, w ; i <= n ; i ++) {
            scanf("%d", &x);
            for(int j = 1 ; j <= x ; j ++) {
                scanf("%d%d", &y, &w);
                dis[i][y] = w;
            }
        }
        for(int k = 1 ; k <= n ; k ++) {
            for(int i = 1 ; i <= n ; i ++) {
                for(int j = 1 ; j <= n ; j ++) {
                    if(i != j) {
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                    }
                }
            }
        }
        int ans = 0x3f3f3f3f, id = 0;
        for(int i = 1 ; i <= n ; i ++) {
            int tmp = -1;
            for(int j = 1 ; j <= n ; j ++) {
                if(i != j) {
                    tmp = max(tmp, dis[i][j]);
                }
            }
            if(ans > tmp) {
                ans = tmp;
                id = i;
            }
        }
        printf("%d %d\n", id, ans);
    }
}
