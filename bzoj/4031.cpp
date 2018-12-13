#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const ll p = 1e9;
 
const int N = 20;
 
int n, m, mp[N][N], d[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}, c[N][N], cnt;
 
ll ans, A[110][110], rev;
 
void add(int x, int y) {
    for(int i = 0, a = c[x][y] ; i < 4 ; ++ i) {
        int u = x + d[i][0], v = y + d[i][1];
        if(c[u][v]) {
            ++ A[a][a], A[a][c[u][v]] = -1;
        }
    }
}
 
char s[N];
 
ll ab(ll x) { return x > 0 ? x : -x; }
 
void sol(int n) {
    for(int i = 1, x ; i <= n ; ++ i) {
        x = i;
        for(int j = i + 1 ; j <= n ; ++ j) {
            if(ab(A[j][i]) > ab(A[x][i])) {
                x = j;
            }
        }
        rev ^= x != i;
        for(int j = 1 ; j <= n ; ++ j) swap(A[i][j], A[x][j]);
        for(int j = i + 1 ; j <= n ; ++ j) {
            while(A[j][i]) {
                ll tmp = A[j][i] / A[i][i];
                for(int k = 1 ; k <= n ; ++ k) {
                    A[j][k] = (A[j][k] + p - tmp * A[i][k] % p) % p;
                }
                if(!A[j][i]) break;
                rev ^= 1;
                for(int k = 1 ; k <= n ; ++ k) swap(A[j][k], A[i][k]);
            }
        }
    }
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s + 1);
        for(int j = 1 ; j <= m ; ++ j) {
            if(s[j] == '*') mp[i][j] = 1;
            else c[i][j] = ++ cnt;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(mp[i][j] != 1) {
                add(i, j);
            }
        }
    }
    sol(cnt - 1);
    ans = 1;
    for(int i = 1 ; i < cnt ; ++ i) ans = (ans * A[i][i]) % p;
    printf("%lld\n", (ans * (rev ? -1 : 1) % p + p) % p);
}
