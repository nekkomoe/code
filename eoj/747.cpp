#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 10;

int n;
char a[N], b[N];

int runprog() {
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1);
    int cnt = 0, mx = 0, sum = 0;

    for(int i = 1 ; i <= n ; ++ i) {
        if(b[i] == '#') {
            return 0;
        }
        cnt += a[i] == '.';
        cnt += b[i] == '.';
        if(a[i] == '#') {
            mx = max(mx, ++ sum);
        } else {
            sum = 0;
        }
    }

    return cnt >= mx + 3;
}

int main() {
    // freopen("swap.in", "r", stdin);
    // freopen("swap.out", "w", stdout);
    int t; scanf("%d", &t);
    while(t --) {
        puts(runprog() ? "Possible" : "Impossible");
    }
}
