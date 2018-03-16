#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int n, len;

typedef complex<double> c;

c a[N], b[N], f[N];

int x, y;

int rev(int x) {
    int res = 0;
    for(int i = 0 ; (1 << i) < len ; ++ i) (res <<= 1) |= (x >> i) & 1;
    return res;
}

void fft(c *t, int ty) {
    
    for(int i = 0 ; i < len ; ++ i) f[rev(i)] = t[i];
    
    for(int i = 2 ; i <= len ; i <<= 1) {
        c wn(cos(2 * acos(-1) / i), ty * sin(2 * acos(-1) / i));
        for(int j = 0 ; j < len ; j += i) {
            c w(1);
            for(int k = j ; k < j + i / 2 ; ++ k) {
                c u = f[k], v = w * f[k + i / 2];
                f[k] = u + v, f[k + i / 2] = u - v;
                w *= wn;
            }
        }
    }
    
    for(int i = 0 ; i < len ; ++ i) t[i] = (f[i] /= (ty == 1 ? 1 : len));
}

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; ++ i) scanf("%d%d", &x, &y), a[i] = x, b[i] = y;
    reverse(b, b + n);
    for(len = 1 ; len <= 2 * n ; len <<= 1) ;
    fft(a, 1), fft(b, 1);
    for(int i = 0 ; i < len ; ++ i) a[i] *= b[i];
    fft(a, -1);
    for(int i = n - 1 ; i < 2 * n - 1 ; ++ i) printf("%d\n", (int) (a[i].real() + 0.1));
}
