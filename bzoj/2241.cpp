#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int sum, mp[N][N], t[N][N], n, m, ans = 0x3f3f3f3f;

void sol(int x, int y) {
    memcpy(t, mp, sizeof t);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(t[i][j]) {
                if(i + x <= n + 1 && j + y <= m + 1) {
                    int tmp = t[i][j];
                    for(int k = 0 ; k < x ; ++ k) {
                        for(int l = 0 ; l < y ; ++ l) {
                            if((t[i + k][j + l] -= tmp) < 0) {
                                return ;
                            }
                        }
                    }
                } else {
                    return ;
                }
            }
        }
    }
    ans = sum / (x * y);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &mp[i][j]), sum += mp[i][j];
        }
    }
    for(int i = n ; i ; -- i) {
        for(int j = m ; j ; -- j) {
            if(!(sum % (i * j)) && ans > sum / (i * j)) {
                sol(i, j);
            }
        }
    }
    printf("%d\n", ans);
}
