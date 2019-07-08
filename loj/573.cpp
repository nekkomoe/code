#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 1e6 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

int n, m, ty;
ll nekko;

int read() {
    int x = 0, c = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}

struct Mat {
    ll a[2][2];
    Mat() {
        memset(a, 0, sizeof a);
    }
    ll *operator [] (int x) {
        return a[x];
    }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i) {
            for(int j = 0 ; j < 2 ; ++ j) {
                for(int k = 0 ; k < 2 ; ++ k) {
                    upd(c[i][j], a[i][k] * b[k][j] % mod);
                }
            }
        }
        return c;
    }
    void init(int x) {
        a[0][0] = x, a[0][1] = 1;
        a[1][0] = 1, a[1][1] = 0;
        /*
            x 1
            1 0
            您好，有逆的
        */
    }
    void getinv(int x) {
        // 您好，要求逆的
        // 您好，注意所有数字都要是非负整数
        /*
            0 1
            1 -x
        */
        a[0][0] = 0, a[0][1] = 1;
        a[1][0] = 1, a[1][1] = mod - x % mod;
    }

    void output() {
        for(int i = 0 ; i < 2 ; ++ i) {
            for(int j = 0 ; j < 2 ; ++ j) {
                printf("%lld ", a[i][j]);
            }
            puts("");
        }
        puts("");
    }

} mat[N], rev[N];
// 矩阵，和逆矩阵

void modify(int x) {
    ++ n;
    mat[n].init(x);
    rev[n].getinv(x);

    // printf("x = %d\n", x);

    // printf("new mat\n");
    // mat[n].output();
    // rev[n].output();

    if(n - 1 >= 1) {
        mat[n] = mat[n] * mat[n - 1];
        rev[n] = rev[n - 1] * rev[n];
    }
    // printf("n = %d\n", n);
}

void ask(int l, int r) {
    // printf("ask %d, %d\n", l, r);
    Mat res;
    res[0][0] = 1;
    res = res * mat[r];

    if(l - 1 >= 1) {
        res = res * rev[l - 1];
    }

    ll up = res[0][0], dn = res[0][1];
    nekko = up ^ dn;
    printf("%lld %lld\n", up, dn);
}

int main() {
    n = read(), m = read(), ty = read();
    // printf("n = %d, m = %d, ty = %d\n", n, m, ty);
    int tn = n; n = 0;
    for(int i = 1 ; i <= tn ; ++ i) {
        modify(read());
        // printf("res %d\n", read());
    }
    // return 0;
    while(m --) {
        int op = read();
        // printf("res op = %d\n", op);
        if(op == 1) {
            int x = read();
            if(ty == 1) {
                x ^= nekko;
            }
            modify(x);
        } else {
            int l = read(), r = read();
            if(ty == 1) {
                l ^= nekko, r ^= nekko;
            }
            ask(l, r);
        }
    }
}
