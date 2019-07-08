#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7, N = 1e5 + 10;
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
 
ll getinv(ll n) {
    return pw(n, mod - 2);
}
 
void upd(ll &a, ll b) {
    a = (a + b) % mod;
}
 
int n;
char str[N];
int f[N];
int cnt[N];
int vis[N];
 
void print(int i) {
    if(i <= 0) {
        return ;
    } else {
        vis[i] = 1;
        for(int j = 0 ; j < i ; ++ j) {
            if(cnt[i] - cnt[j] != i - j - (cnt[i] - cnt[j])) {
                print(j);
                break;
            }
        }
    }
}
 
int main() {
    scanf("%d%s", &n, str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        cnt[i] = cnt[i - 1] + (str[i] == '1');
    }
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j < i ; ++ j) {
            if(cnt[i] - cnt[j] != i - j - (cnt[i] - cnt[j])) {
                f[i] = min(f[i], f[j] + 1);
            }
        }
    }
    printf("%d\n", f[n]);
    print(n);
    int lst = 0;
    for(int i = 1 ; i <= n ; ) {
        if(vis[i]) {
            for(int j = lst + 1 ; j <= i ; ++ j) {
                printf("%c", str[j]);
            }
            putchar(' ');
            lst = i;
            ++ i;
        } else {
            ++ i;
        }
    }
    if(lst < n) {
        for(int j = lst + 1 ; j <= n ; ++ j) {
            printf("%c", str[j]);
        }
        putchar(' ');
    }
}
