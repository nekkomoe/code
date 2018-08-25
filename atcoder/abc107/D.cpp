#include "bits/stdc++.h"
using namespace std;
 
const int N = 1e5 + 10;
 
int n, a[N], val[N], s[N];
 
int bit[N * 2 + 10];
 
void modify(int x) {
    x += n + 2;
    for( ; x <= 2 * n + 10; x += x & -x) ++ bit[x];
}
 
int query(int x) {
    x += n + 2;
    int res = 0;
    for( ; x ; x -= x & -x) res += bit[x];
    return res;
}
 
int check(int val) {
    // puts("go 1");
    for(int i = 0 ; i <= 2 * n + 10 ; ++ i) bit[i] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] <= val) s[i] = 1;
        else s[i] = -1;
        s[i] += s[i - 1];
    }
    long long res = 0, len = 1ll * n * (n + 1) / 2;
    modify(0);
    for(int i = 1 ; i <= n ; ++ i) {
        res += query(s[i] - 1);
        modify(s[i]);
    }
    return res >= len / 2 + 1;
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        val[i] = a[i];
    }
    sort(val + 1, val + 1 + n);
    int k = unique(val + 1, val + 1 + n) - val - 1;
    int l = 1, r = k, ans = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(val[mid])) {
            ans = val[mid];
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", ans);
}
