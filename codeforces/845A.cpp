// 排序 贪心

/*
  给定2n个人，把他们分成两组，使得存在一种排列使得对应的人中第一组的每个人的rating永远比对应的那个人的rating严格大于
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 210;

int n, a[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n * 2 ; i ++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n * 2);
    if(a[n] < a[n + 1]) {
        puts("YES");
    } else {
        puts("NO");
    }
}
