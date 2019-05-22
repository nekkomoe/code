#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 2e6 + 10;

struct Mat {
    int a[10][10];
    int* operator [] (int x) {
        return a[x];
    }
    Mat() {
        memset(a, 0, sizeof a);
    }
    Mat operator * (Mat b) {
        Mat res;
        for(int i = 0 ; i < 10 ; ++ i) {
            for(int j = 0 ; j < 10 ; ++ j) {
                for(int k = 0 ; k < 10 ; ++ k) {
                    res[i][j] = (res[i][j] + (ll) a[i][k] * b[k][j] % mod) % mod;
                }
            }
        }
        return res;
    }
} mts[210];
Mat pw(Mat a, ll b) {
    Mat r;
    for(int i = 0 ; i < 10 ; ++ i) {
        r[i][i] = 1;
    }
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            r = r * a;
        }
    }
    return r;
}
int n, a[N];

int main() {
    // freopen("matrix.in", "r", stdin);
    // freopen("matrix.out", "w", stdout);
    for(int i = 1 ; i <= 10 ; ++ i) {
        for(int j = 0 ; j < 10 ; ++ j) {
            for(int k = 0 ; k < 10 ; ++ k) {
                scanf("%d", &mts[i][j][k]);
            }
        }
    }
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= 100 ; ++ i) {
        int x; scanf("%d", &x);
        for(int j = n ; j > x ; -- j) {
            a[j + 1] = a[j];
        }
        a[x + 1] = 10 + i;
        ++ n;
        for(int j = 0 ; j < 10 ; ++ j) {
            for(int k = 0 ; k < 10 ; ++ k) {
                scanf("%d", &mts[10 + i][j][k]);
            }
        }
    }
    Mat ini;
    for(int i = 0 ; i < 10 ; ++ i) {
        ini[i][i] = 1;
    }
    for(int i = 1 ; i <= n ; ) {
        if(a[i] > 10) {
            ini = ini * mts[a[i]];
            ++ i;
            continue;
        }
        int j = i;
        while(j + 1 <= n && a[j + 1] <= 10) {
            ++ j;
        }
        // [i, j]
        vector<int> cnt(11);
        for(int k = i ; k <= j ; ++ k) {
            ++ cnt[a[k]];
        }
        for(int k = 1 ; k <= 10 ; ++ k) {
            ini = ini * pw(mts[k], cnt[k]);
        }
        if(j + 1 <= n) {
            ini = ini * mts[a[j + 1]];
        }
        i = j + 2;
    }
    for(int i = 0 ; i < 10 ; ++ i) {
        for(int j = 0 ; j < 10 ; ++ j) {
            if(j) putchar(' ');
            printf("%d", ini[i][j]);
        }
        puts("");
    }
}
