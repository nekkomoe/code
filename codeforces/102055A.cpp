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

pair<int, int> a[N];

int n, m;

void runprog() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i].first);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i].second);
    }
    sort(a + 1, a + 1 + n);
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(m - a[i].second < 0) break;
        m -= a[i].second;
        ++ ans;
    }
    static int T = 0;
    printf("Case %d: %d\n", ++ T, ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
