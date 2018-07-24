#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 60;

int n, m;
char mp[N][N];

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct D {
    ll up, dw;
    void mt() {
        ll d = gcd(up, dw);
        up /= d, dw /= d;
    }
    D(ll up = 0, ll dw = 1) : up(up), dw(dw) { mt(); }
    D operator + (D t) {
        ll d = gcd(dw, t.dw);
        return D(up * (t.dw / d) + (dw / d) * t.up, dw / d * t.dw);
    }
    D operator * (D t) { return D(up * t.up, dw * t.dw); }
} f[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= i ; ++ j)
            while(mp[i][j] != '*' && mp[i][j] != '.')
                mp[i][j] = getchar();
    f[1][1] = D(1, 1);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= i ; ++ j)
            if(mp[i][j] == '*')
                f[i + 1][j] = f[i + 1][j] + f[i][j] * D(1, 2),
                f[i + 1][j + 1] = f[i + 1][j + 1] + f[i][j] * D(1, 2);
            else
                f[i + 2][j + 1] = f[i + 2][j + 1] + f[i][j];
    printf("%lld/%lld", f[n + 1][m + 1].up, f[n + 1][m + 1].dw);
}
