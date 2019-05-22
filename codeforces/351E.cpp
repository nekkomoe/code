#include <bits/stdc++.h>
using namespace std;

int n, a[2010];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        int op[2] = { 0, 0 };
        for(int j = 1 ; j <= n ; ++ j) {
            if(abs(a[j]) < abs(a[i])) {
                op[i < j] ++;
            }
        }
        ans += min(op[0], op[1]);
    }
    printf("%d\n", ans);
}
