#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
const int N = 50010;
int n, f[N], a[N], L, lst[int(1e6) + 10], ans;

int main() {
    scanf("%d%d", &n, &L);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        f[i] = 1;
        for(int j = 1 ; j * j <= a[i] ; ++ j) {
            if(a[i] % j == 0) {
                if(j >= L)
                    f[i] = max(f[i], lst[j] + 1);
                if(a[i] / j >= L)
                    f[i] = max(f[i], lst[a[i] / j] + 1);
            }
        }
        for(int j = 1 ; j * j <= a[i] ; ++ j) {
            if(a[i] % j == 0) {
                lst[j] = max(lst[j], f[i]);
                lst[a[i] / j] = max(lst[a[i] / j], f[i]);
            }
        }
        ans = max(ans, f[i]);
    }
    printf("%d\n", ans); 
} 
