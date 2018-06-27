#include "bits/stdc++.h"
using namespace std;
const int mod = 987654321;
typedef long long ll;

// f[i] = 3f[i-1]-f[i-2]

struct Mat {
    ll a[2][2];
    Mat() { memset(a, 0, sizeof a); }
    ll* operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i)
            for(int j = 0 ; j < 2 ; ++ j)
                for(int k = 0 ; k < 2 ; ++ k)
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
        return c;
    }
    Mat operator ^ (int x) {
        Mat t = *this;
        Mat c; c[0][0] = c[1][1] = 1;
        for( ; x ; x >>= 1, t = t * t) if(x & 1) c = c * t;
        return c;
    }
} a, b;

int main() {
    a[0][0] = a[0][1] = 1;
    b[0][1] = mod - 1, b[1][0] = 1, b[1][1] = 3;
    int n; while(scanf("%lld", &n) == 1 && n) {
        if(n % 2 || n == 2) puts("0");
        else printf("%lld\n", (((a * (b ^ (n / 2 - 1)))[0][0] - n / 2 + 1) % mod + mod) % mod);
    }
}
