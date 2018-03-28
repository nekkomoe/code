//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, f[1010];

/*
  f[i] : 前i个灯泡选择完后最小花费

  f[i] min= f[j] + (sumL[i] - sumL[j]) * cost[i]+ k[i]
 */

struct Light {
    int v, k, c, l;
} lights[1010];

bool operator < (Light a, Light b) {
    return a.v < b.v;
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 1 ; i <= n ; i ++) {
            scanf("%d%d%d%d", &lights[i].v, &lights[i].k, &lights[i].c, &lights[i].l);
        }
        sort(lights + 1, lights + 1 + n);
        for(int i = 1 ; i <= n ; i ++) {
            lights[i].l += lights[i - 1].l;
        }
        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        for(int i = 1 ; i <= n ; i ++) {
            for(int j = 0 ; j < i ; j ++) {
                f[i] = min(f[i], f[j] + (lights[i].l - lights[j].l) * lights[i].c + lights[i].k);
            }
        }
        printf("%d\n", f[n]);
    }
}
