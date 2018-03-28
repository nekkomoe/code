//dp

%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int N = 200020;

namespace OI {
    int a[N], left[N], right[N], n, ans = 0xcfcfcfcf;

    int main() {
        scanf("%d", &n);
        for(int i = 1 ; i <= n ; i ++) {
            scanf("%d", &a[i]);
        }
        for(int i = 1 ; i <= n ; i ++) {
            left[i] = max(0, left[i - 1]) + a[i];
        }
        for(int i = n ; i >= 1 ; i --) {
            right[i] = max(0, right[i + 1]) + a[i];
        }
        for(int i = 1 ; i <= n ; i ++) {
            ans = max(ans, left[i] + right[i] - a[i]);
        }
        printf("%d\n", ans);
        return 0;
    }
}

int main() {
    OI :: main();
}