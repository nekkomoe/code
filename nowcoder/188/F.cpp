#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
 
ll n, m, S;
 
struct Mat {
    int a[1 << 5][1 << 5];
    Mat() { memset(a, 0, sizeof a); }
    void clear() { memset(a, 0, sizeof a); }
    int *operator [] (int x) { return a[x]; }
    Mat operator * (Mat b) {
        Mat c;
//      for(int i = 0 ; i < S ; ++ i)
//          for(int k = 0 ; k < S ; ++ k)
//              if(a[i][k])
//                  for(int j = 0 ; j < S ; ++ j)
//                      c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j] % mod) % mod;
        for(int i = 0 ; i < S ; ++ i)
            for(int j = 0 ; j < S ; ++ j)
                for(int k = 0 ; k < S ; ++ k)
                    c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j] % mod) % mod;
        return c;
    }
};
 
Mat pw(Mat a, ll b) {
    Mat r;
    for(int i = 0 ; i < S ; ++ i) r[i][i] = 1;
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            r = r * a;
        }
    }
    return r;
}
 
bool check(int S) {
    int cnt = 0;
    for(int i = 0 ; i < m ; ++ i)
        if((S >> i) & 1)
            ++ cnt;
    // 0: 3, 1: 7
    return m - cnt >= cnt;
}
 
Mat init, a;
 
int at(int x, int y) {
    return (x >> y) & 1;
}
 
int main() {
    cin >> n >> m;
    S = 1 << m;
    for(int i = 0 ; i < S ; ++ i)
        if(check(i)) {
            for(int j = 0 ; j <= 1 ; ++ j) {
                int x = i - (at(i, m - 1) << (m - 1));
//              cout << bitset<10>(x) << " " << bitset<10>(i) << endl;
                int k = (x << 1) | j;
                if(check(k)) {
                    a[i][k] = 1;
                }
            }
        }
 
    ++ n;
    Mat mt = pw(a, n-1);
    ll ans = 0;
    for(int i=0;i<S;i++)
        if(check(i))
        {
            init.clear();
            init[0][i]=1;
            init=init*mt;
            (ans+=init[0][i])%=mod;
        }
    cout<<ans;
    /*for(int i = 0 ; i < S ; ++ i) {
        init[0][i] = 0;
        if(check(i))
            init[0][i] = at(i, m - 1) == 1;
    }
    Mat x = init * mt;
    for(int i = 0 ; i < S ; ++ i)
        if(check(i))
            if(at(i, 0) == 1)
                ans = (ans + x[0][i]) % mod;
 
    for(int i = 0 ; i < S ; ++ i) {
        init[0][i] = 0;
        if(check(i))
            init[0][i] = at(i, m - 1) == 0;
    }
    x = init * mt;
    for(int i = 0 ; i < S ; ++ i)
        if(check(i))
            if(at(i, 0) == 0)
                ans = (ans + x[0][i]) % mod;*/
 
}
