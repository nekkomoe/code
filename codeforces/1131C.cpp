#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1100;

int n, a[N];

int ans[N], top;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    ans[1] = a[1], ans[2] = a[2];
    for(int i = 3 ; i <= n ; ++ i) {
        int pos = 1, val = max(ans[i] - ans[1], ans[i] - ans[i - 1]);
        for(int j = 2 ; j < i ; ++ j) {
            int newval = max(ans[i] - ans[j - 1], ans[i] - ans[j]);
            if(newval < val) {
                val = newval;
                pos = j;
            }
        }
//        printf("pos = %d\n", pos);
        for(int k = i - 1 ; k >= pos ; -- k) {
            ans[k + 1] = ans[k];
        }
        ans[pos] = a[i];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", ans[i]);
    }
}
