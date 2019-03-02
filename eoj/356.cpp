#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = (1ll << 20) + 10, lim = 1ll << 20;

ll a[N];

void fwt(ll *f, int ty, int n) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) {
                    f[k] = u;
                    f[k + i / 2] = u + v;
                } else {
                    f[k] = u;
                    f[k + i / 2] = u - v;
                }
            }
        }
    }
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        ++ a[x];
    }
    fwt(a, 0, lim);
    for(int i = 0 ; i < lim ; ++ i) a[i] *= a[i];
    fwt(a, 1, lim);
    for(int i = lim - 1 ; ~ i ; -- i) {
        if(a[i]) {
            printf("%d\n", i);
            return 0;
        }
    }
}
