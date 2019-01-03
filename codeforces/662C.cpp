#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char str[30][int(1e5) + 10];
int n, m;
const int N = (1 << 20) + 10;
ll a[N], b[N], cnt[N];

void fwt(ll *f, int ty) {
    int n = 1 << :: n;
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j + i / 2 < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) f[k] = u + v, f[k + i / 2] = u - v;
                else f[k] = (u + v) >> 1, f[k + i / 2] = (u - v) >> 1;
            }
        }
    }
} 

int main() {
    
	ios :: sync_with_stdio(0);
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str[i] + 1);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int x = 0;
        for(int j = 1 ; j <= n ; ++ j) {
            x = x * 2 + str[j][i] - '0';
        }
        ++ a[x];
    }
    for(int i = 0 ; i < (1 << n) ; ++ i) {
        cnt[i] = cnt[i >> 1] + (i & 1);
        b[i] = min(cnt[i], n - cnt[i]);
    }
    
//    for(int i = 0 ; i < (1 << n) ; ++ i) {
//        cout << a[i] << ' ' << b[i] << endl;
//    }
    
    fwt(a, 0), fwt(b, 0);
    for(int i = 0 ; i < (1 << n) ; ++ i) {
        a[i] *= b[i];
    }
    fwt(a, 1);
    ll ans = a[0];
    for(int i = 0 ; i < (1 << n) ; ++ i) {
        ans = min(ans, a[i]);
    }
    printf("%lld\n", ans);
}

