#include <bits/stdc++.h>
using namespace std; typedef long long ll;
ll n, k, p, r;
struct Mat {
    ll a[55][55];
    Mat() { memset(a, 0, sizeof a); }
    ll* operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < k ; ++ i)
            for(int j = 0 ; j < k ; ++ j)
                for(int w = 0 ; w < k ; ++ w)
                    c[i][j] = (c[i][j] + a[i][w] * b[w][j] % p) % p;
        return c;
    }
} a;
Mat pw(Mat a, ll b) {
    Mat c;
    for(int i = 0 ; i < k ; ++ i) c[i][i] = 1;
    for( ; b ; b >>= 1, a = a * a)
        if(b & 1)
            c = c * a;
    return c;
}

int main() {
    cin >> n >> p >> k >> r;
    // f[i][j] = f[i - 1][j] + f[i - 1][(j - 1) % k]
    for(int j = 0 ; j < k ; ++ j)
        a[j][j] ++,
        a[j][((j - 1) % k + k) % k] ++;
    cout << pw(a, n * k)[0][r] << endl;
}
