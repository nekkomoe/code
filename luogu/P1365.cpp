#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10, K = 12, mod = 1e9 + 7;

int n, k, C[K][K];

double e[N][K], ans;

char s[N];

int main() {
    k = 2;
    scanf("%d%s", &n, s + 1);
    C[0][0] = 1;
    for(int i = 1 ; i <= k ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= k ; ++ j) {
            C[i][j] = 1ll * C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        double p;
        if(s[i] == 'o') p = 1;
        else if(s[i] == 'x') p = 0;
        else p = 0.5;
        e[i - 1][0] = 1; double tmp = 0;
        for(int j = 1 ; j <= k ; ++ j) {
            for(int t = 0 ; t <= j ; ++ t) {
                e[i][j] += C[j][t] * e[i - 1][t];
            }
            tmp = e[i][k];
            e[i][j] *= p;
        }
        ans += p * (tmp - e[i - 1][k]);
    }
    printf("%.4lf\n", ans);
} 