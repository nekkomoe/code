#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 30, mod = 1e9 + 7;
 
struct Mat {
    ll a[N][N];
    ll* operator [] (int x) {
        return a[x];
    }
    Mat() {
        memset(a, 0, sizeof a);
    }
    Mat operator * (Mat b) {
        Mat res;
        for(int i = 0 ; i < 26 ; ++ i) {
            for(int j = 0 ; j < 26 ; ++ j) {
                for(int k = 0 ; k < 26 ; ++ k) {
                    res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
                }
            }
        }
        return res;
    }
} nek, coef;
 
char str[int(1e5) + 10];
 
int ban[30][30];
 
Mat pw(Mat a, ll b) {
    Mat res;
    for(int i = 0 ; i < 26 ; ++ i) {
        res[i][i] = 1;
    }
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            res = res * a;
        }
    }
    return res;
}
 
int main() {
    ll T; scanf("%lld", &T);
    scanf("%s", str + 1);
    for(int i = 1 ; str[i] ; ++ i) {
        if(i > 1) {
            int u = str[i - 1] - 'a';
            int v = str[i] - 'a';
            ban[u][v] = 1;
        }
    }
    for(int i = 0 ; i < 26 ; ++ i) {
        nek[0][i] = 1;
    }
    for(int i = 0 ; i < 26 ; ++ i) {
        for(int j = 0 ; j < 26 ; ++ j) {
            if(!ban[i][j]) {
                coef[i][j] = 1;
            }
        }
    }
    nek = nek * pw(coef, T - 1);
    ll ans = 0;
    for(int i = 0 ; i < 26 ; ++ i) {
        ans = (ans + nek[0][i]) % mod;
    }
    printf("%lld\n", ans);
}
