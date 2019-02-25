#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 110;

int n, p[N], vis[N];
char a[N][N];

bitset<N> f[N];

int check1() {
    for(int i = 1 ; i <= n ; ++ i) {
        if(f[i].count() == n) {
            return 1;
        }
    }
    return 0;
}

int check2() {
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            if((f[i] | f[j]).count() == n) {
                return 1;
            }
        }
    }
    return 0;
}

int check3() {
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            for(int k = 1 ; k < j ; ++ k) {
                if((f[i] | f[j] | f[k]).count() == n) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check4() {
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            for(int k = 1 ; k < j ; ++ k) {
                for(int a = 1 ; a < k ; ++ a) {
                    if((f[i] | f[j] | f[k] | f[a]).count() == n) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int check5() {
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            for(int k = 1 ; k < j ; ++ k) {
                for(int a = 1 ; a < k ; ++ a) {
                    for(int b = 1 ; b < k ; ++ b) {
                        if((f[i] | f[j] | f[k] | f[a] | f[b]).count() == n) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    int tot = 0;
    while(scanf("%d", &n) == 1) {
        printf("Case %d: ", ++ tot);
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%s", a[i] + 1);
            f[i] = 0;
            f[i].set(i);
            for(int j = 1 ; j <= n ; ++ j) {
                if(a[i][j] == '1') {
                    f[i].set(j);
                }
            }
        }
        if(check1()) { puts("1"); continue; }
        if(check2()) { puts("2"); continue; }
        if(check3()) { puts("3"); continue; }
        if(check4()) { puts("4"); continue; }
        if(check5()) { puts("5"); continue; }
        puts("6");
    }
}
