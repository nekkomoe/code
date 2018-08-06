#include "bits/stdc++.h"
using namespace std;
int main() {
    int n; scanf("%d", &n);
    if(n <= 3) {
        // 1 2 3
        puts("NO");
    } else if(n == 4) {
        // 1 2 3 4
        puts("YES");
        puts("1 * 2 = 2");
        puts("2 * 3 = 6");
        puts("6 * 4 = 24");
    } else if(n == 5) {
        // 1 2 3 4 5
        puts("YES");
        puts("3 - 1 = 2");
        puts("2 + 2 = 4");
        puts("4 * 5 = 20");
        puts("20 + 4 = 24");
    } else if(n == 6) {
        // 1 2 3 4 5 6
        puts("YES");
        puts("5 * 6 = 30");
        puts("3 - 2 = 1");
        puts("1 + 1 = 2");
        puts("4 + 2 = 6");
        puts("30 - 6 = 24");
    } else if(n == 7) {
        // 1 2 3 4 5 6 7
        puts("YES");
        puts("3 - 1 = 2");
        puts("2 + 2 = 4");
        puts("4 * 5 = 20");
        puts("20 + 4 = 24");
        puts("7 - 6 = 1");
        puts("1 * 24 = 24");
    } else {
        // 1 2 3 4    5 6 7 8 ...
        puts("YES");
        puts("1 * 2 = 2");
        puts("2 * 3 = 6");
        puts("6 * 4 = 24");
        puts("6 - 5 = 1");
        puts("8 - 7 = 1");
        puts("1 - 1 = 0");
        for(int i = 9 ; i <= n ; ++ i) printf("0 * %d = 0\n", i);
        puts("24 + 0 = 24");
    }
}

