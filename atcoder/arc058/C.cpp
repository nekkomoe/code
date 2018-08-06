// 贪心 暴力

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>

using namespace std;

int n, k, d[15], bit[15];

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1, x ; i <= k ; ++ i) {
        scanf("%d", &x);
        d[x] = 1;
    }
    for(int i = n, p, w ; (w = i, p = 1) ; ++ i) {
        while(w) {
            bit[p ++] = w % 10;
            w /= 10;
        }
        for(int j = 1 ; j < p ; ++ j) {
            if(d[bit[j]]) {
                goto nxt;
            }
        }
        printf("%d\n", i);
        break;
    nxt:;
    }
}
