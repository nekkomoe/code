#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 3e5 + 10;

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

int n, m, a[N], b[N];
int check(int cnt) {
    for(int i = 1 ; i <= n ; ++ i) {
        b[i] = a[i];
    }
    int lst = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] < lst) {
            if(lst - a[i] > cnt) {
                return 0;
            }
        } else if(a[i] > lst) {
            if(m - a[i] + lst > cnt) {
                lst = a[i];
            }
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = b[i];
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    int l = 0, r = m, res = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", res);
}
