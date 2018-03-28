//数组统计

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

int T, a[300], ans, n;

int main() {
    scanf("%d", &T);
    while(T --) {
        memset(a, 0, sizeof(a));
        ans = 0;
        scanf("%d", &n);
        for(int i = 1, l, r ; i <= n ; i ++) {
            scanf("%d%d", &l, &r);
            if(l > r) swap(l, r);
            int x = (l - 1) / 2, y = (r - 1) / 2;
            for(int j = x ; j <= y ; j ++) {
                a[j] += 10;
            }
        }
        for(int i = 0 ; i < 200 ; i ++) {
            ans = max(ans, a[i]);
        }
        printf("%d\n", ans);
    }
}
