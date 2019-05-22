#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1 << 24;

ll a[N], b[N];
int _n = 1, n = 1, k;

int f(int x) {
    int r = 0, prod = 1;
    while(x) {
        r += prod * (x % 3);
        x /= 3;
        prod *= 4;
    }
    return r;
}

template<typename T> void fwt(ll *a, int n, T t) {
    for(int i = 1 ; i < n ; i *= 4) {
        for(int j = 0, len = i * 4 ; j < n ; j += len) {
            for(int k = 0 ; k < i ; ++ k) {
                t(a[j + k], a[j + i + k], a[j + 2 * i + k], a[j + 3 * i + k]);
            }
        }
    }
}

void C(ll &a, ll &b, ll &c, ll &d) {
    ll x[4] = { a, b, c, d };
    a = x[1] + x[2];
    b = x[0] + x[1] + x[2];
    c = x[0] + x[2];
    d = x[2];
}

void D(ll &a, ll &b, ll &c, ll &d) {
    ll x[4] = { a, b, c, d };
    a = x[0];
    b = x[2] - x[3];
    c = x[1] - x[0] - x[2] + x[3];
}

int main() {
    scanf("%d", &k);
    for(int i = 1 ; i <= k ; ++ i) {
        _n *= 3;
        n *= 4;
    }

    for(int i = 0 ; i < _n ; ++ i) {
        scanf("%lld", &a[f(i)]);
    }
    for(int i = 0 ; i < _n ; ++ i) {
        scanf("%lld", &b[f(i)]);
    }

    fwt(a, n, C), fwt(b, n, C);
    for(int i = 0 ; i < n ; ++ i) {
        a[i] *= b[i];
    }
    fwt(a, n, D);

    for(int i = 0 ; i < _n ; ++ i) {
        printf("%lld ", a[f(i)]);
    }
}
