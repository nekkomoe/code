#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n; char str[N];

void runprog() {
    scanf("%d%s", &n, str + 1);
    int x = 0, cnt = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(str[i] == 'P') {
            ++ cnt;
        }
    }
    for(int i = 3 ; i <= n - 2 ; ++ i) {
        if(str[i] == 'A') {
            // (x + cnt) / n >= 3 / 4
            // 4 * (x + cnt) >= 3 * n
            if(4 * (x + cnt) < 3 * n) {
                if((str[i - 1] == 'P' || str[i - 2] == 'P')
                && (str[i + 1] == 'P' || str[i + 2] == 'P')) {
                    ++ x;
                }
            }
        }
    }
    printf("%d\n", 4 * (x + cnt) >= 3 * n ? x : -1);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
