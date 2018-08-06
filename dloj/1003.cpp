#pragma GCC optimize(2)
 
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
const int N = 500000 * 2 + 10;
 
int pos, ans, rl[N], len, maxRight;
 
int n, a[N], q, mx[N][30], lg[N];
 
int check(int l, int r, int mid) {
    // printf("checking: [%d, %d], %d\n", l, r, mid);
    int len = r - l + 1;
    int k = lg[len];
    return max(mx[l][k], mx[r - (1 << k) + 1][k]) >= mid;
}
 
int sol(int ql, int qr) {
    ans = 0;
    int l = 1, r = qr - ql + 1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(check(2 * ql + mid - 1, 2 * qr - mid + 1, mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}
 
void init() {
    len = n;
    for(int i = len - 1 ; i >= 0 ; -- i) a[2 * i + 1] = a[i];
    len = len * 2 + 1;
    for(int i = 2 ; i <= len ; ++ i) lg[i] = lg[i >> 1] + 1;
    for(int i = 0 ; i < len ; ++ i)
        if(!(i & 1))
            a[i] = '#';
    for(int i = 0 ; i < len ; ++ i) {
        if(i < maxRight)
            rl[i] = min(rl[2 * pos - i], maxRight - i);
        else
            rl[i] = 1;
        while(i - rl[i] >= 0 && i + rl[i] < len && a[i - rl[i]] == a[i + rl[i]])
            ++ rl[i];
        if(i + rl[i] - 1 > maxRight) {
            maxRight = i + rl[i] - 1;
            pos = i;
        }
        // ans = max(ans, rl[i] - 1);
    }
    for(int i = 0 ; i < len ; ++ i) mx[i + 1][0] = -- rl[i];
     
    // for(int i = 1 ; i <= len ; ++ i) {
    //     printf("%d ", mx[i][0]);
    // }
    // puts("");
    // for(int i = 1 ; i <= len ; ++ i) printf("%d ", a[i - 1] == '#' ? 0 : a[i - 1]);
    // puts("");
 
    for(int j = 1 ; j <= 25 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= len ; ++ i) {
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        }
    }
}
 
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 0 ; i < n ; ++ i) scanf("%d", &a[i]);
    init();
    while(q --) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", sol(l, r));
        // puts("-----------");
    }
}
