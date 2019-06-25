#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 500000 + 10;

int n, q;
int fa[N];
double f[N][62];

void upd(int x, int son, int clk) {
    if(!x || clk > 60) return ;
    if(fa[x] && clk + 1 <= 60) {
        for(int i = 1 ; i <= 60 ; ++ i) {
            f[fa[x]][i] /= 0.5 * (f[x][i - 1] + 1);
        }
    }
    for(int i = 1 ; i <= 60 ; ++ i) {
        f[x][i] *= 0.5 * (f[son][i - 1] + 1);
    }
    upd(fa[x], x, clk + 1);
}

int main() {
    scanf("%d", &q);
    n = 1;
    for(int i = 0 ; i <= 60 ; ++ i) {
        f[1][i] = 1;
    }
    while(q --) {
        int op, x; scanf("%d%d", &op, &x);
        if(op == 1) {
            fa[++ n] = x;
            for(int i = 0 ; i <= 60 ; ++ i) {
                f[n][i] = 1;
            }
            double coef = f[x][0];
            f[x][0] *= 0.5;
            for(int i = 1, f = fa[x] ; f && i <= 60 ; x = fa[x], f = fa[x], ++ i) {
                double tmp = :: f[f][i];
                :: f[f][i] /= 0.5 * (1 + coef);
                :: f[f][i] *= 0.5 * (1 + :: f[x][i - 1]);
                coef = tmp;
            }
        } else {
            double ans = 0;
            for(int i = 1 ; i <= 60 ; ++ i) {
                ans += (f[x][i] - f[x][i - 1]) * i;
            }
            printf("%.6lf\n", ans);
        }
    }
}
