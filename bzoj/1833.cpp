#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll f[20][20][20], pw[20], ans[20];
void sol(ll n, ll ty) {
    ans[0] += ty;
    if(n) {
        int len = 15;
        while(pw[len] > n) -- len;
        for(int i = 1 ; i < len ; ++ i) {
            for(int j = 1 ; j <= 9 ; ++ j) {
                for(int k = 0 ; k <= 9 ; ++ k) {
                    ans[k] += f[i][j][k] * ty;
                }
            }
        }
        int cur = n / pw[len];
        for(int i = 1 ; i < cur ; ++ i) {
            for(int j = 0 ; j <= 9 ; ++ j) {
                ans[j] += f[len][i][j] * ty;
            }
        }
        n %= pw[len];
        ans[cur] += ty * (n + 1);
        for(int i = len - 1 ; i ; -- i) {
            cur = n / pw[i];
            for(int j = 0 ; j < cur ; ++ j) {
                for(int k = 0 ; k <= 9 ; ++ k) {
                    ans[k] += ty * f[i][j][k];
                }
            }
            n %= pw[i];
            ans[cur] += ty * (n + 1);
        }
    }
}

int main() {
    ll l, r; scanf("%lld%lld", &l, &r);
    pw[1] = 1;
    for(int i = 2 ; i <= 15 ; ++ i) pw[i] = pw[i - 1] * 10;
    for(int i = 0 ; i <= 9 ; ++ i) f[1][i][i] = 1;
    for(int len = 2 ; len <= 15 ; ++ len) {
        for(int i = 0 ; i <= 9 ; ++ i) {
            for(int j = 0 ; j <= 9 ; ++ j) {
                for(int k = 0 ; k <= 9 ; ++ k) {
                    f[len][j][k] += f[len - 1][i][k];
                }
                f[len][j][j] += pw[len - 1];
            }
        }
    }

    sol(r, 1), sol(l - 1, -1);
    for(int i = 0 ; i <= 9 ; ++ i) {
        if(i > 0) putchar(' ');
        printf("%lld", ans[i]);
    }
}

