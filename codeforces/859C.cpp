// dp 博弈论

/*
  给你n个物品，bob和alice轮流顺序取物品（有价值），如果当前取的人把当前物品给了对方，下回合仍然是该人进行
  两个人都十分聪明，并且都想尽可能的价值最大
  求两个人得到的最大价值分别是多少
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 60;

int n, a[N], f[N], sum[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &a[i]);
    }
    for(int i = n ; i ; i --) {
        sum[i] = sum[i + 1] + a[i];
        f[i] = max(f[i + 1], sum[i + 1] - f[i + 1] + a[i]);
    }
    printf("%d %d\n", sum[1] - f[1], f[1]);
}
