// 矩阵乘法 快速幂 动态规划

%:pragma GCC optimize(2)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

typedef long long ll;

ll n, m, k, t;

struct mat {
    ll a[3][3];
    int row, col;
    void resize(int rw, int cl) {
        row = rw;
        col = cl;
        for(int i = 0 ; i < rw ; ++ i) {
            for(int j = 0 ; j < col ; ++ j) {
                a[i][j] = 0;
            }
        }
    }
};

mat meta, init;

inline mat mul(mat a, mat b) {
    mat ret;
    ret.resize(a.row, b.col);
    ll kk = k;
    for(int i = 0 ; i < a.row ; ++ i) {
        for(int j = 0 ; j < a.col ; ++ j) {
            for(int k = 0 ; k < b.row ; ++ k) {
                a.a[i][k] %= kk;
                b.a[k][j] %= kk;
                ret.a[i][j] = (ret.a[i][j] + a.a[i][k] * b.a[k][j]) % kk;
            }
        }
    }
    return ret;
}

inline mat ksm(mat a, ll n) {
    mat ret;
    ret.resize(a.row, a.col);
    for(int i = 0 ; i < ret.row ; ++ i)
        for(int j = 0 ; j < ret.col ; ++ j)
            ret.a[i][j] = i == j;
    while(n) {
        if(n & 1) {
            ret = mul(ret, a);
        }
        n >>= 1;
        a = mul(a, a);
    }
    return ret;
}

int main() {
    // freopen("testdata.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    meta.resize(2, 2);
    init.resize(1, 2);
    while(m --) {
        scanf("%lld", &t);
        meta.a[0][0] = 1 + t;
        meta.a[0][1] = 1;
        meta.a[1][0] = -t;
        meta.a[1][1] = 0;
        meta.a[1][0] = (meta.a[1][0] + (int)1e9 * k) % k;
        init.a[0][0] = 1 + t;
        init.a[0][1] = 1;
        printf("%lld\n", mul(init, ksm(meta, n - 1)).a[0][1]);
    }
}
