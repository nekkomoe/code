#include <bits/stdc++.h>

using namespace std;

int q, n;

struct mat {
    int a[2][2];
    int *operator [] (int x) {
        return a[x];
    }
    mat() { memset(a, 0, sizeof a); }
};

mat mul(mat a, mat b) {
    mat c;
    for(int i = 0 ; i < 2 ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            for(int k = 0 ; k < 2 ; ++ k) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= 5;
            }
        }
    }
    return c;
}

mat pw(mat a, int k) {
    mat c; c[0][0] = c[1][1] = 1;
    for( ; k ; k >>= 1, a = mul(a, a)) if(k & 1) c = mul(c, a);
    return c;
}

void sol() {
    scanf("%d", &n);
    mat a; a[0][0] = a[0][1] = a[1][0] = 1;
    a = pw(a, n - 1);
    printf("%d\n", (a[1][0] + a[1][1]) % 5);
}

int main() {
    scanf("%d", &q);
    while(q --) sol();
}
