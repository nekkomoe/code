#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 10;
int n;
ll a[N], k, x;
ll b[N];

void runprog() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
    }
    scanf("%lld%lld", &k, &x);
    if(k == n) {
        ll p = 0, q = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            p += a[i];
            q += a[i] ^ x;
        }
        printf("%lld\n", max(p, q));
    } else {
        ll sum = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            b[i] = (a[i] ^ x) - a[i];
            sum += a[i];
        }
        sort(b + 1, b + 1 + n, greater<ll> ());
        vector<ll> lt, eq, gt;
        for(int i = 1 ; i <= n ; ++ i) {
            if(b[i] < 0) {
                lt.emplace_back(b[i]);
            } else if(b[i] == 0) {
                eq.emplace_back(b[i]);
            } else {
                gt.emplace_back(b[i]);
            }
        }

        ll ans = sum;        
        if(k & 1) {
            // all
            for(ll x: gt) {
                ans += x;
            }
        } else {
            // even
            ll tmp = 0;
            for(int i = 1 ; i + 1 <= n ; i += 2) {
                tmp += b[i] + b[i + 1];
                ans = max(ans, sum + tmp);
            }
        }

        printf("%lld\n", ans);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
