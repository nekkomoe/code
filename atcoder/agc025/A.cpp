#include "bits/stdc++.h"
using namespace std;
int n;
int get(int x) {
    int res = 0;
    while(x) res += x % 10, x /= 10;
    return res;
}
int main() {
    scanf("%d", &n);
    int ans = get(1) + get(n - 1);
    for(int i = 1 ; i < n ; ++ i) ans = min(ans, get(i) + get(n - i));
    printf("%d\n", ans);
}
