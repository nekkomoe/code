#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 410, mod = 1e9 + 7; 

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int n;
ll a[N][N * 2];

void poi() {
    puts("No Solution");
    exit(0);
}

void output() {
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            printf("%lld ", a[i][j]);
        }
        printf(" | ");
        for(int j = n + 1 ; j <= n * 2 ; ++ j) {
            printf("%lld ", a[i][j]);
        }
        puts("");
    }
    puts("");
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%lld", &a[i][j]);
            a[i][j] %= mod;
        }
        a[i][n + i] = 1;
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        int ch = i;
        for(int j = i ; j <= n ; ++ j) {
            if(a[j][i]) {
                ch = j;
                break;
            }
        }
        for(int j = i ; j <= n * 2 ; ++ j) {
            swap(a[i][j], a[ch][j]);
        }
        if(!a[i][i]) poi();
        for(int j = i + 1 ; j <= n ; ++ j) {
            ll x = a[j][i] * pw(a[i][i], mod - 2) % mod;
            for(int k = i ; k <= n * 2 ; ++ k) {
                (a[j][k] -= a[i][k] * x % mod) %= mod;
            }
        }
    }
    
    for(int i = n ; i >= 1 ; -- i) {
        if(!a[i][i]) poi();
        for(int j = i - 1 ; j >= 1 ; -- j) {
            ll x = a[j][i] * pw(a[i][i], mod - 2) % mod;
            for(int k = i ; k <= n * 2 ; ++ k) {
                (a[j][k] -= a[i][k] * x % mod) %= mod;
            }
        }
        ll x = pw(a[i][i], mod - 2);
        for(int j = i ; j <= n * 2 ; ++ j) {
            (a[i][j] *= x) %= mod;
        }
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = n + 1 ; j <= n * 2 ; ++ j) {
            printf("%lld ", (a[i][j] % mod + mod) % mod);
        }
        puts("");
    }
}

