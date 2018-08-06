#include "bits/stdc++.h"
using namespace std;
int n, m, cnt[110];
bool check(int day) {
    int tot = 0;
    for(int i = 1 ; i <= 100 ; ++ i) {
        tot += cnt[i] / day;
    }
    return tot >= n;
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, x ; i <= m ; ++ i) {
        scanf("%d", &x);
        ++ cnt[x];
    }
    for(int i = 100 ; i ; -- i) {
        if(check(i)) {
            printf("%d\n", i);
            return 0;
        }
    }
    puts("0");
}
