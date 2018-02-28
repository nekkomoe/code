#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;

const int N = 1e6 + 10;

#define pi acos(-1)

typedef complex<double> c;

c F[N], A[N], B[N];

int n;

double q;

int rev(int x, int n) {
    int ret = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) ret = (ret << 1) | ((x & (1 << i)) > 0);
    return ret;
}

void fft(c *a, int n, int f) {
    for(int i = 0 ; i < n ; ++ i) F[rev(i, n)] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        c wn = c(cos(2 * pi * f / i), sin(2 * pi * f / i));
        for(int j = 0 ; j < n ; j += i) {
            c w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k){
                c u = F[k], t = w * F[k + i / 2];
                F[k] = u + t;
                F[k + i / 2] = u - t;
                w *= wn;
            }
        }
    }
    for(int i = 0 ; i < n ; ++ i) a[i] = (F[i] /= (f == -1 ? n : 1));
}

int main()
{
    scanf("%d",&n), -- n;
    for(int i = 0 ; i <= n ; ++ i) scanf("%lf", &q), A[i] = q;
    for(int i = 0 ; i < n ; ++ i)
        B[i] = (-1.0) / ((double)(n - i) * (double)(n - i));
    for(int i = n + 1 ; i <= 2 * n ; ++ i)
        B[i] = -B[2 * n - i];
    int m = 4 * n, nn = n;
    for(n = 1 ; n <= m ; n <<= 1);
    fft(A, n, 1), fft(B, n, 1);
    for(int i = 0 ; i <= n ; ++ i) A[i] *= B[i];
    fft(A, n, -1);
    for(int i = nn ; i <= 2 * nn ; ++ i) printf("%lf\n", A[i].real());
}
