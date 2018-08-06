#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;
int n, m, a[N];
int main() {
    scanf("%d%d", &n, &m);
    int use = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        int ans = 0;
        if(m - use >= a[i]) {
            use += a[i];
            ans = 0;
            if(use == m) {
                use = 0;
                ans = 1;
            }
        } else {
            a[i] -= m - use;
            use = a[i] % m;
            ans = 1 + (a[i] / m);
        }
        // cout << "use = " << use << endl;
        printf("%d ", ans);
    }
}
