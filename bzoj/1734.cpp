#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
int n, c, a[N];
bool check(int mid) {
    int c = :: c - 1;
    for(int i = 2, last = 1 ; i <= n ; ++ i) {
        if(a[i] - a[last] >= mid) {
            -- c;
            last = i;
        }
    }
    return c <= 0;
}
int main() {
    scanf("%d%d", &n, &c);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    int l = 0, r = 1e9, ans;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);
}
