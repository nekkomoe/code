//差分数组（静态区间修改，区间查询）

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int N = 200010, M = 200005;

int a[N], n, k, vis[N], q, mx;

int main() {
    freopen("coffee.in", "r", stdin);
    freopen("coffee.out", "w", stdout);
    scanf("%d%d%d", &n, &k, &q);
    for(int i = 1, l, r ; i <= n ; i ++) {
        scanf("%d%d", &l, &r);
        a[l] ++;
        a[r + 1] --;
        mx = max(mx, r + 1);
    }
    for(int i = 1 ; i <= M ; i ++) {
        vis[i] += vis[i - 1] + ((a[i] += a[i - 1]) >= k);
    }
    for(int i = 1, l, r ; i <= q ; i ++) {
        scanf("%d%d", &l, &r);
        printf("%d\n", vis[r] - vis[l - 1]);
    }
}
