#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, ans = 1, pos[N];
int main() {
    scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        pos[x] = i;
    }
    for(int i = 2, cnt = 1 ; i <= n ; ++ i) {
        if(pos[i] > pos[i - 1]) ans = max(ans, ++ cnt);
        else cnt = 1;
    }
    printf("%d\n", n - ans);
}
