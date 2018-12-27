#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4 * 2e5 + 10;
typedef complex<double> c;

int n, inp[N], x, cnt;

ll ans[N];

c a[N], b[N], f[N];

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i)
        r = (r << 1) | ((x >> i) & 1);
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
                w = w * wn;
            }
        }
    }
    
    for(int i = 0 ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty == -1) {
            a[i] /= n;
        }
    } 
}

int A[N], B[N];

int main() {
    ios :: sync_with_stdio();
    cin >> n >> x;
    for(int i = 1 ; i <= n ; ++ i) cin >> inp[i], inp[i] = inp[i] < x, inp[i] += inp[i - 1];
    
    for(int i = 1 ; i <= n ; ++ i) ++ A[inp[i - 1]];
    for(int i = 1 ; i <= n ; ++ i) ++ B[inp[n] - inp[i]];
    for(int i = 0 ; i <= n ; ++ i) a[i] = A[i], b[i] = B[i];
    int len = 1; while(len <= 2 * n + 10) len <<= 1;
    
    fft(a, len, 1), fft(b, len, 1);
    for(int i = 0 ; i < len ; ++ i) a[i] = a[i] * b[i];
    fft(a, len, -1);

    for(int i = 0 ; i < inp[n] ; ++ i) {
        ans[inp[n] - i] = (ll) (a[i].real() + 0.5);
    } 
    
    for(int i = 1, len = 0 ; i <= n + 1 ; ++ i) {
        if(i == n + 1 || inp[i] - inp[i - 1]) ans[0] += (ll) len * (len + 1) / 2, len = 0;
        else ++ len;
    }
    
    for(int i = 0 ; i <= n ; ++ i)
        cout << ans[i] << ' ';
}

