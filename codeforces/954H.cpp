#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5010, mod = 1e9 + 7, inv2 = 500000004;

int f[N][N * 2], ans[2 * N], prod[N]; 
int n, a[N];

int main() {
//    freopen("data.in", "r", stdin); 
	ios :: sync_with_stdio(0);
    scanf("%d", &n);
    prod[1] = 1;
    for(int i = 1 ; i < n ; ++ i) {
        scanf("%d", &a[i]);
        prod[i + 1] = (ll) prod[i] * a[i] % mod;
    }
    f[n][0] = 1;
    for(int i = n - 1 ; i >= 1 ; -- i) {
        f[i][0] = 1;
        for(int j = 1 ; j <= n ; ++ j) {
            f[i][j] = (ll) a[i] * f[i + 1][j - 1] % mod;
            ans[j] = (ans[j] + (ll) prod[i] * f[i][j] % mod) % mod;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) f[1][i] = 0;
    for(int i = 2 ; i <= n ; ++ i) {
        for(int j = 2 * n - 2 ; j >= 1 ; -- j) {
            f[i][j] = f[i - 1][j - 1];
            if(j >= 2) {
                f[i][j] = (f[i][j] + (ll) (a[i - 1] - 1) * f[i][j - 2] % mod) % mod;
            } 
            ans[j] = (ans[j] + (ll) prod[i] * f[i][j] % mod) % mod;
        }
    }
    for(int i = 1 ; i <= 2 * n - 2 ; ++ i)
        printf("%d ", int(((ll) ans[i] * inv2 % mod + mod) % mod)); 
}

