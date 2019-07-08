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

char str[int(1e6) + 10];

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        int n;
        scanf("%d%s", &n, str + 1);
        int m = strlen(str + 1), x = 0;
        for(int i = 1 ; i <= m ; ++ i) {
            x = (x * 10 + str[i] - '0') % n;
        }
        int y = n - x;
        printf("%d\n", 2 * min(x, y) - (x == y));
    }    
}

/*
首先肯定把 k %= n
设 x=k%n,y=n-x
也就是有x个1，y个0
如果 x=y: 2x-1
如果 x<y: 2x
如果 x>y: 2y
*/
