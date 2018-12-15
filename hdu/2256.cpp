#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1024;

ll n;

struct Mat {
    ll a[2][2];
    Mat() { memset(a, 0, sizeof a); }
    ll *operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i)
            for(int j = 0 ; j < 2 ; ++ j)
                for(int k = 0 ; k < 2 ; ++ k)
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j] % mod) % mod;
        return c;
    } 
}; 

Mat pw(Mat a, ll b) {
    Mat r;
    for(int i = 0 ; i < 2 ; ++ i) r[i][i] = 1;
    for( ; b ; b >>= 1, a = a * a)
        if(b & 1)
            r = r * a;
    return r;
}

void sol() {
    Mat base, rat;
    base[0][0] = 5, base[1][0] = 2;
    rat[0][0] = 5, rat[1][0] = 2;
    rat[0][1] = 12, rat[1][1] = 5;
    ll n; cin >> n;
    cout << ((2 * (pw(rat, n - 1) * base)[0][0] - 1) % mod + mod) % mod << endl;
}

int main() {
    ios :: sync_with_stdio();
    int t; cin >> t;
    while(t --) sol();
}

