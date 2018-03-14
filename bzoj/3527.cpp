#include <bits/stdc++.h>

using namespace std;
 
const int N = 1000010;
 
typedef complex<double> c;

c f[N], a[N], b[N];

int n;

double q[N], ans[N];

int rev(int x, int n) {
    int res = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) (res <<= 1) |= ((x >> i) & 1);
    return res;
}

void fft(c *t, int n, int ty) {
    
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = t[i];
    
    for(int i = 2 ; i <= n ; i <<= 1) {
        c wn(cos(2 * acos(-1) / i), ty * sin(2 * acos(-1) / i));
        for(int j = 0 ; j < n ; j += i) {
            c w(1);
            for(int k = j ; k < j + i / 2 ; ++ k) {
                c u = f[k], v = w * f[k + i / 2];
                f[k] = u + v;
                f[k + i / 2] = u - v;
                w *= wn;
            }
        }
    }
    
    for(int i = 0 ; i < n ; ++ i) t[i] = (f[i] /= (ty == 1 ? 1 : n));
}

int main() {
    int len;
    
    scanf("%d", &n);

    for(int i = 0 ; i < n ; ++ i) scanf("%lf", &q[i]);
    
    for(int i = 0 ; i < n ; ++ i) a[i] = q[i], b[i] = (i ? 1.0 / i / i : 0);
    
    for(len = 1 ; len < 4*n ; len <<= 1) ;
    
    fft(a, len, 1);
    
    fft(b, len, 1);
    
    for(int i = 0 ; i < len ; ++ i) a[i] *= b[i];
    
    fft(a, len, -1);
    
    for(int i = 0 ; i < n ; ++ i) ans[i] = a[i].real();
    
    for(int i = 0 ; i < len ; ++ i) a[i] = b[i] = 0;
    
    for(int i = 0 ; i < n ; ++ i) a[i] = q[n - 1 - i], b[i] = (i ? 1.0 / i / i : 0);
    
    fft(a, len, 1);
    
    fft(b, len, 1);
    
    for(int i = 0 ; i < len ; ++ i) a[i] *= b[i];
    
    fft(a, len, -1);
    
    for(int i = 0 ; i < n ; ++ i) ans[i] -= a[n - 1 - i].real();
    
    for(int i = 0 ; i < n ; ++ i) printf("%lf\n", ans[i]);
    
}
