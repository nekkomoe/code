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
int deg[N];

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        ++ deg[u], ++ deg[v];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(deg[i] == 2) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
}
