#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, a[N];

#define x(i, j) (a[i] <= T && a[j] <= T)
#define y(i, j) (a[i] > T && a[j] > T)

bool check(int T) {
    for(int len = 1 ; len <= 2 * n ; ++ len) {
        int i = n + len - 1, j = i + 1;
        int p = n - len + 1, q = p - 1;
        if(1 <= i && i <= 2 * n - 1
        && 1 <= j && j <= 2 * n - 1
        && 1 <= p && p <= 2 * n - 1
        && 1 <= q && q <= 2 * n - 1) {
            if(x(i, j) || x(p, q)) return 1;
            if(y(i, j) || y(p, q)) return 0;
        }
    } 
    return x(1, 1);
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= 2 * n - 1 ; ++ i)
        scanf("%d", &a[i]);
    int l = 1, r = 2 * n - 1, ans = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    } 
    printf("%d\n", ans); 
}

