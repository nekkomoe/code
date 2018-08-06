#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, k, a[N];
int main() {
    scanf("%d%d", &n, &k);
    int pos;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        if(a[i] == 1) pos = i;
    }
    int ans = n;
    for(int i = max(1, pos - k + 1) ; i <= pos ; ++ i) {
        int j = i + k - 1;
        ans = min(ans, (i - 1 + k - 2) / (k - 1) + (n - j + k - 2) / (k - 1) + 1);
    }
    printf("%d\n", ans);
}
