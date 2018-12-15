#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 7528443412579576937ll;
ll b, d, n;

ll mul(ll a, ll b) {
    ll res = 0;
    for(a %= mod, b %= mod ; b ; b >>= 1, a = ((__int128) a + a) % mod) {
        if(b & 1) {
            res = ((__int128) res + a) % mod;
        }
    }
    return res;
}

struct Mat {
    ll a[2][2];
    Mat() { memset(a, 0, sizeof a); }
    ll *operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i)
            for(int j = 0 ; j < 2 ; ++ j)
                for(int k = 0 ; k < 2 ; ++ k)
                    c[i][j] = ((__int128) c[i][j] + mul(a[i][k], b[k][j]) % mod) % mod;
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
    if(n == 0) return cout << 1 << endl, void();
    Mat base, rat;
    base[0][0] = b % mod, base[0][1] = 2;
    rat[0][0] = b % mod, rat[1][0] = (d - b * b) / 4;
    rat[0][1] = 1, rat[1][1] = 0;
    ll t = (base * pw(rat, n - 1))[0][0];
    if(n % 2 == 0 && b * b != d)
        -- t;
    t = ((__int128) t % mod + mod) % mod;
    cout << t << endl;
}

int main() {
    ios :: sync_with_stdio();
    cin >> b >> d >> n;
    sol(); 
}

