#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int a[N], b[N], l1, r1, l2, r2, mod, t1, t2;

void put(int l, int r, int *a) {
    if(r - l >= mod) {
        for(int i = 0 ; i < mod ; ++ i) a[i] = 1;
    } else if(t1 <= t2) {
        for(int i = t1 ; i <= t2 ; ++ i) a[i] = 1;
    } else {
        for(int i = 0 ; i <= t2; ++ i) a[i] = 1;
        for(int i = t1 ; i < mod ; ++ i) a[i] = 1;
    }
}

void sol() {
    memset(a, 0 ,sizeof a), memset(b, 0, sizeof b);
    scanf("%d%d%d%d%d", &l1, &r1, &l2, &r2, &mod);
    t1 = l1 % mod, t2 = r1 % mod;
    put(l1, r1, a);
    t1 = l2 % mod, t2 = r2 % mod;
    put(l2, r2, b);
    for(int i = 0 ; i < mod ; ++ i) {
        if(a[i] == 1 && b[(mod - i) % mod] == 0) {
            puts("WIN");
            return ;
        }
    }
    puts("LOSE");
}

int main() {
    int T; scanf("%d", &T);
    while(T --) sol();
}
