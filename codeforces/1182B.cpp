#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7;
 
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
 
const int N = 510;
char str[N][N];
int n, m;
int lef[N][N], rig[N][N];
int up[N][N], dn[N][N];
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str[i] + 1);
    }
    int shp = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(str[i][j] == '*') {
                lef[i][j] = lef[i][j - 1] + 1;
                up[i][j] = up[i - 1][j] + 1;
                ++ shp;
            }
        }
    }
    for(int i = n ; i >= 1 ; -- i) {
        for(int j = m ; j >= 1 ; -- j) {
            if(str[i][j] == '*') {
                rig[i][j] = rig[i][j + 1] + 1;
                dn[i][j] = dn[i + 1][j] + 1;
            }
        }
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(str[i][j] == '*') {
                if(min(min(lef[i][j], rig[i][j]), min(up[i][j], dn[i][j])) > 1 && lef[i][j] + rig[i][j] + up[i][j] + dn[i][j] - 3 == shp) {
                    puts("YES");
                    return 0;
                }
            }
        }
    }
    puts("NO");
}
