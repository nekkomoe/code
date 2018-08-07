#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, q, cnt[N][30];
char s[N];
void sol() {
    scanf("%d%d%s", &n, &q, s + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j < 26 ; ++ j) {
            cnt[i][j] = cnt[i - 1][j];
        }
        ++ cnt[i][s[i] - 'A'];
    }
    for(int i = 1, l, r ; i <= q ; ++ i) {
        scanf("%d%d", &l, &r);
        for(int j = 0 ; j < 26 ; ++ j) if(cnt[r][j] - cnt[l - 1][j]) { printf("%d\n", cnt[r][j] - cnt[l - 1][j]); break; }
    }
}
int main() {
    int T; scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++ i) {
        printf("Case #%d:\n", i);
        sol();
    }
}
