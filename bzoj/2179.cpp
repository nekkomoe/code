#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n;

typedef complex<double> c;

c f[N], a[N], b[N];
 
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

char s1[N], s2[N];

int ans[N];

int main() {
    scanf("%d%s%s", &n, s1, s2);
    
    for(int i = 0 ; i < n ; ++ i) a[i] = s1[n - i - 1] - '0', b[i] = s2[n - i - 1] - '0';
    
    int len = 1;
    for( ; len < 2 * n ; len <<= 1) ;
    
    fft(a, len, 1), fft(b, len, 1);
    
    for(int i = 0 ; i < len ; ++ i) a[i] *= b[i];
    
    fft(a, len, -1);
    
//    for(int i=0;i<len;i++) 
//        printf("i=%d,ans=%d\n",i,(int)(a[i].real()+0.3));
    
    int lim=2*n-1;
    for(int i = 0 ; i < lim ; ++ i) {
        ans[i] += int(a[i].real() + 0.1);
        if(ans[i] >= 10) {
            ans[i + 1] += ans[i] / 10, ans[i] %= 10;
        } 
    }
    if(ans[lim])
        lim++;
    
    
    for(int i =lim-1  ; ~i ; -- i) printf("%d", ans[i]);
    
}
