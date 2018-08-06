//模拟
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int a[110], n, x, tot, flag, ans;

int main() {
    scanf("%d%d", &n, &x);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &a[i]);
        if(a[i] < x) {
            tot ++;
        }
        if(a[i] == x) {
            flag = 1;
        }
    }
    if(flag) {
        ans = x - tot + 1;
    } else {
        ans = x - tot;
    }

    printf("%d\n", ans);
}
