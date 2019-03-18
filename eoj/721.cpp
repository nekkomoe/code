#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll pw[20];
double f[20][20][2][2];

int n, m, ln, lm;

int nxt[20], dig_n[20], dig_m[20];

double dfs(int len, int p, int lim, int led) {
    if(len < 0) return !led;
    double &res = f[len + 1][p + 1][lim][led];
    if(res != -1) {
        return res;
    }
    res = 0;
    for(int i = 0 ; i <= (lim ? dig_n[len] : 9) ; ++ i) {
        int j = p;
        if(!led || i) {
            while(j != -1 && i != dig_m[j + 1]) {
                j = nxt[j];
            }
            if(i == dig_m[j + 1]) {
                ++ j;
            }
        }
        if(j == lm) continue;
        res += exp((double) i * pw[len] / n) * dfs(len - 1, j, lim && i == dig_n[len], led && i == 0);
    }
    return res;
}

int main() {
    for(int i = 0 ; i < 20 ; ++ i) {
        for(int j = 0 ; j < 20 ; ++ j) {
            for(int a = 0 ; a < 2 ; ++ a) {
                for(int b = 0 ; b < 2 ; ++ b) {
                    f[i][j][a][b] = -1;
                }
            }
        }
    }
    scanf("%d%d", &n, &m);
    pw[0] = 1;
    for(int i = 1 ; i <= 10 ; ++ i) pw[i] = pw[i - 1] * 10;
    for(int i = 0 ; i < 10 ; ++ i) {
        if(pw[i + 1] > n) {
            ln = i;
            break;
        }
    }
    for(int i = 0 ; i < 10 ; ++ i) {
        if(pw[i + 1] > m) {
            lm = i;
            break;
        }
    }
    for(int i = 0, x = n ; i <= ln ; ++ i) {
        dig_n[i] = x % 10;
        x /= 10;
    }
    for(int i = lm, x = m ; i >= 0 ; -- i) {
        dig_m[i] = x % 10;
        x /= 10;
    }
    nxt[0] = -1;
    for(int i = 1, j = -1 ; i <= lm ; ++ i) {
        while(j != -1 && dig_m[j + 1] != dig_m[i]) {
            j = nxt[j];
        }
        if(dig_m[i] == dig_m[j + 1]) {
            ++ j;
        }
        nxt[i] = j;
    }
    printf("%.3lf\n", dfs(ln, -1, 1, 1));
}
