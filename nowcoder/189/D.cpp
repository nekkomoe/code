#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
struct Mat {
    ll a[3][3];
    Mat() { memset(a, 0, sizeof a); }
    ll* operator [] (int x) { return a[x]; }
};
  
Mat operator * (Mat a, Mat b) {
    Mat c;
    for(int i = 0 ; i < 3 ; ++ i)
        for(int j = 0 ; j < 3 ; ++ j)
            for(int k = 0 ; k < 3 ; ++ k)
                c[i][j] = ((ll) c[i][j] + a[i][k] * b[k][j] % mod) % mod;
    return c;
}
  
Mat pw(Mat a, ll n) {
    Mat c;
    for(int i = 0 ; i < 3 ; ++ i) c[i][i] = 1;
    for( ; n ; n >>= 1, a = a * a) {
        if(n & 1) {
            c = c * a;
        }
    }
    return c;
}
  
int main() {
    ll k; scanf("%lld", &k);
    if(k == 0) puts("1"), exit(0);
    Mat bs;
    bs[0][0] = 1, bs[0][1] = 1, bs[0][2] = 1;
    bs[1][0] = 1, bs[1][1] = 0, bs[1][2] = 1;
    bs[2][0] = 0, bs[2][1] = 0, bs[2][2] = 1;
    Mat init;
    init[0][0] = 1, init[0][1] = 1, init[0][2] = 2;
    Mat ans = init * pw(bs, k - 1);
    printf("%lld\n", ans[0][2]);
}
