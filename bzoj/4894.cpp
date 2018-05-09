#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

const int N = 310;

char s[N];

int a[N][N], n, d[N][N];

typedef long long ll;

ll ans, v[N][N];

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%s", s);
        for(int j = 0 ; j < n ; ++ j) {
            a[i][j] = s[j] - '0';
            if(a[i][j]) ++ d[j][j];
        }
    }
    for(int i = 1 ; i < n ; ++ i) {
        for(int j = 1 ; j < n ; ++ j) {
            v[i][j] = d[i][j] - a[i][j];
            v[i][j] = (v[i][j] % mod + mod) % mod;
        }
    }
    ll ans = 1;
    for(int i = 1, j ; i < n ; ++ i) {
        for(j = i ; j < n ; ++ j) if(v[i][j]) break;
        if(j != i) {
            ans = (-ans % mod + mod) % mod;
            for(int k = i ; k < n ; ++ k) swap(v[i][k], v[j][k]);
        }
        for(j = i + 1 ; j < n ; ++ j) {
            ll A = v[i][i], B = v[j][i];
            while(B) {
                cout << B << endl;
                int tmp = A / B;
                int t = A; A = B; B = t % B;
                ans = (-ans % mod + mod) % mod;
                for(int k = i ; k < n ; ++ k) {
                    v[i][k] = (v[i][k] - tmp * v[j][k] % mod + mod) % mod;
                    swap(v[i][k], v[j][k]);
                }
            }
        }
        ans = ans * v[i][i] % mod;
    }
    printf("%lld\n", ans);
}
