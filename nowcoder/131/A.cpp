#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int lef[N], rig[N], a[N], n, m, beg, en;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    if(n == 1) {
        printf("%d", a[1]);
        return 0;
    }
    for(int i = 1 ; i <= n ; ++ i) lef[a[i]] = a[i - 1], rig[a[i]] = a[i + 1];
    beg = a[1], en = a[n];
    scanf("%d", &m);
    for(int i = 1, x ; i <= m ; ++ i) {
        char op[10];
        scanf("%s%d", op, &x);
        if(op[0] == 'F') {
            if(x == beg) continue;
            if(lef[x]) rig[lef[x]] = rig[x];
            if(rig[x]) lef[rig[x]] = lef[x];
            if(x == en) en = lef[x];
            rig[x] = beg;
            lef[beg] = x;
            lef[x] = 0;
            beg = x;
        } else {
            if(x == en) continue;
            if(lef[x]) rig[lef[x]] = rig[x];
            if(rig[x]) lef[rig[x]] = lef[x];
            if(x == beg) beg = rig[x];
            lef[x] = en;
            rig[en] = x;
            rig[x] = 0;
            en = x;
        }
        lef[0] = rig[0] = 0;
        // printf("i = %d\n", i);
        // for(int i = 1 ; i <= n ; ++ i) printf("%d %d\n", lef[i], rig[i]);
        // puts("");
    }
    for(int x = beg, t = 0 ; x ; x = rig[x]) {
        if(t == 0) t = 1;
        else putchar(' ');
        printf("%d", x);
    }
}
