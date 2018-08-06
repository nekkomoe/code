// 枚举 贪心 排序

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

const int N = 60;

int w[N], n, ans, val[N], w2[N], p, ansp;

int main() {
    scanf("%d", &n);
    // 事实上有2 * n个人
    n *= 2;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &w[i]);
    }
    sort(w + 1, w + 1 + n);

    ans = 0x3f3f3f3f;

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            // i和j坐单人船
            p = 0;
            for(int k = 1 ; k <= n ; ++ k) {
                if(k != i && k != j) {
                    w2[++ p] = w[k];
                }
            }
            ansp = 0;
            for(int k = 1 ; k < p ; k += 2) {
                ansp += abs(w2[k] - w2[k + 1]);
            }
            ans = min(ans, ansp);
        }
    }

    printf("%d\n", ans);
}
