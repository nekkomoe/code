#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, D = 110;

int n, d, mod, a[N][D], ids[N];

void prt(int x, int y) {
    if(x > y) swap(x, y);
    printf("%d %d\n", x, y);
}

namespace sol_mod2 {
    int b[D];

    inline int check(int x, int y) {
        int z = 0;
        for(int i = 1 ; i <= d ; ++ i) {
            z ^= a[x][i] & a[y][i];
        }
        return !z;
    }
    inline int getsum(int x) {
        int r = 0;
        for(int i = 1 ; i <= d ; ++ i) {
            r ^= a[x][i] & b[i];
            b[i] ^= a[x][i];
        }
        return r;
    }

    void runprog() {
        for(int i = 2 ; i <= n ; ++ i) {
            swap(ids[i], ids[rand() % (i - 1) + 1]);
        }
        for(int i = 1 ; i <= n ; ++ i) {
            if(getsum(ids[i]) != ((i - 1) & 1)) {
                for(int j = 1 ; j < i ; ++ j) {
                    if(check(ids[j], ids[i])) {
                        prt(ids[j], ids[i]);
                        exit(0);
                    }
                }
            }
        }
    }
}

namespace sol_mod3 {
    int b[D][D];

    inline int check(int x, int y) {
        int z = 0;
        for(int i = 1 ; i <= d ; ++ i) {
            (z += a[x][i] * a[y][i]) %= 3;
        }
        return !z;
    }
    inline int getsum(int x) {
        int r = 0;
        for(int i = 1 ; i <= d ; ++ i) {
            for(int j = 1 ; j <= d ; ++ j) {
                (r += a[x][i] * a[x][j] * b[i][j]) %= 3;
                (b[i][j] += a[x][i] * a[x][j]) %= 3;
            }
        }
        return r;
    }

    void runprog() {
        for(int i = 2 ; i <= n ; ++ i) {
            swap(ids[i], ids[rand() % (i - 1) + 1]);
        }
        for(int i = 1 ; i <= n ; ++ i) {
            if(getsum(ids[i]) != ((i - 1) % 3)) {
                for(int j = 1 ; j < i ; ++ j) {
                    if(check(ids[j], ids[i])) {
                        prt(ids[j], ids[i]);
                        exit(0);
                    }
                }
            }
        }
    }
}

int main() {
    srand(1234978);
    scanf("%d%d%d", &n, &d, &mod);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= d ; ++ j) {
            scanf("%d", &a[i][j]);
            a[i][j] %= mod;
        }
        ids[i] = i;
    }
    if(mod == 2) {
        sol_mod2 :: runprog();
    } else {
        sol_mod3 :: runprog();
    }
    puts("-1 -1");
}
