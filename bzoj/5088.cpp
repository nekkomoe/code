#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
ll a[N], ans;
priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > p1, p2;
int main() {
    int L, n, m;
    scanf("%d%d%d", &L, &n, &m);
    for(int i = 1, x ; i <= n ; ++ i) scanf("%d", &x), p1.push(make_pair(x, x));
    for(int i = 1, x ; i <= m ; ++ i) scanf("%d", &x), p2.push(make_pair(x, x));
    for(int i = 1 ; i <= L ; ++ i) {
        a[i] = p1.top().first; ll t = p1.top().second;
        p1.pop();
        p1.push(make_pair(a[i] + t, t));
    }
    for(int i = L ; i ; -- i) {
        ll x = p2.top().first, y = p2.top().second; p2.pop();
        ans = max(ans, a[i] + x);
        p2.push(make_pair(x + y, y));
    }
    printf("%lld\n", ans);
}
