#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
 
int n, q, cnt[N][40], a[N];
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        for(int j = 30 ; ~ j ; -- j) {
            cnt[i][j] = cnt[i - 1][j] + ((a[i] >> j) & 1);
        }
    }
    scanf("%d", &q);
    for(int i = 1 ; i <= q ; ++ i) {
        int l, r; scanf("%d%d", &l, &r);
        int x = 0, len = r - l + 1;
        for(int j = 30 ; ~ j ; -- j) {
            int sum = cnt[r][j] - cnt[l - 1][j];
            if(sum < len - sum) {
                x |= 1 << j;
            }
        }
         
        printf("%d\n", x);
    }
}
