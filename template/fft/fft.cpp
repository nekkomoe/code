#include "bits/stdc++.h"
using namespace std;
typedef complex<double> c;
const int N = 4e6 + 10;

int n, m;

c a[N], b[N], f[N];

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) r = (r << 1) | ((x >> i) & 1);
    return r;
}

void fft(c *a, int n, int ty) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];

    for(int i = 2 ; i <= n ; i <<= 1) {
        c wn = c(cos(2 * acos(-1) * ty / i), sin(2 * acos(-1) * ty / i));
        for(int j = 0 ; j < n ; j += i) {
            c w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                c u = f[k], v = w * f[k + i / 2];
                f[k] = u + v;
                f[k + i / 2] = u - v;
                w *= wn;
            }
        }
    }

    for(int i = 0 ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty == -1) a[i] /= n;
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m, ++ n, ++ m;
    for(int i = 0 ; i < n ; ++ i) cin >> a[i];
    for(int i = 0 ; i < m ; ++ i) cin >> b[i];
    int len = 1; while(len <= n + m + 5) len <<= 1;
    fft(a, len, 1), fft(b, len, 1);
    for(int i = 0 ; i < len ; ++ i) a[i] *= b[i];
    fft(a, len, -1);
    for(int i = 0 ; i < n + m - 1 ; ++ i) cout << int(a[i].real() + 0.5) << ' ';
}