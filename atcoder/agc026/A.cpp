#include "bits/stdc++.h"
using namespace std;
const int N = 110;
int n, a[N], ans;
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] == a[i - 1]) {
            a[i] = 0;
            ++ ans;
        }
    }
    printf("%d\n", ans);
}
