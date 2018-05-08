#include <bits/stdc++.h>

using namespace std;

const int N = 30;

int n, w[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &w[i]), w[i] += w[i - 1];
    }
    if(w[n] & 1) return puts("0"), 0;
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            if(w[j] - w[i] == (w[n] >> 1)) {
                ++ ans;
            }
        }
    }
    printf("%d\n", ans * (ans - 1) / 2);
}
