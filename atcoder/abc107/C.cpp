#include "bits/stdc++.h"
using namespace std;
 
const int N = 1e5 + 10;
 
int n, k, a[N], b[N];
 
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        if(a[i] == 0) {
            -- k;
            a[i] = 1e9;
        }
    }
    sort(a + 1, a + 1 + n);
    if(a[n] == int(1e9)) -- n;
    if(k == 0) {
        puts("0");
        return 0;
    }
    int ans = abs(a[1]) + a[n] - a[1];
    if(0 < a[1]) {
        ans = a[k];
    } else if(a[n] < 0) {
        ans = 0 - a[n - k + 1];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] <= 0 && 0 <= a[i + 1]) {
            if(i - k + 1 >= 1) {
                ans = min(ans, 0 - a[i - k + 1]);
            }
            if(i + k <= n) {
                ans = min(ans, a[i + k]);
            }
            for(int j = 1 ; j <= k ; ++ j) {
                int l = i - (k - j) + 1, r = i + j;
                if(1 <= l && r <= n) {
                    ans = min(ans, a[r] + (a[r] - a[l]));
                }
            }
            for(int j = 1 ; j <= k ; ++ j) {
                int l = i - j + 1, r = i + (k - j);
                if(1 <= l && r <= n) {
                    ans = min(ans, 0 - a[l] + (a[r] - a[l]));
                }
            }
            break;
        }
    }
    printf("%d\n", ans);
}
