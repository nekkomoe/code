#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 510, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int n, a[N][N]; ll inp[N];

ll pri[2010], poi[2010], tot;

int getrank(int n, int m) {
    int i = 1, j = 1;
    while(i <= n && j <= m) {
        int row = i;
        for(int k = i ; k <= n ; ++ k)
            if(a[k][j]) {
                row = k;
                break;
            }
        if(a[row][j]) {
            for(int k = 1 ; k <= m ; ++ k) swap(a[row][k], a[i][k]);
            for(int x = i + 1 ; x <= n ; ++ x)
                if(a[x][j])
                    for(int y = j ; y <= m ; ++ y)
                        a[x][y] ^= a[i][y];
            ++ i;
        }
        ++ j;
    }
    return i - 1;
}

void sol() {
    scanf("%d", &n); int mx = 0;
    memset(a, 0, sizeof a);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &inp[i]);
        for(int j = 1 ; j <= tot && pri[j] <= inp[i] ; ++ j) {
            if(inp[i] % pri[j] == 0) {
                mx = max(mx, j);
                while(inp[i] % pri[j] == 0) {
                    inp[i] /= pri[j];
                    a[j][i] ^= 1;
                }
            }
        }
    }
    printf("%lld\n", pw(2, n - getrank(mx, n)) - 1); 
}

int main() {
    for(int i = 2 ; i <= 2000 ; ++ i) {
        if(!poi[i]) {
            for(int j = i + i ; j <= 2000 ; j += i) {
                poi[j] = 1;
            }
            pri[++ tot] = i;
        }
    }
    int T; scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++ i) {
        printf("Case #%d:\n", i);
        sol();
    }
}

