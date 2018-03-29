#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll inf = 1e16;

const int N = 4000010;

ll dis[N], mn, h, a, b, c, inq[N], x[3];

void spfa() {
    memset(dis, 0x3f, sizeof dis);
    queue<ll> q;
    q.push(0), inq[0] = 1, dis[0] = 0;
    while(q.size()) {
        ll x = q.front(); q.pop(); inq[x] = 0;
        for(int i = 0 ; i < 3 ; ++ i) {
            ll y = (x + :: x[i]) % mn;
            if(dis[y] > dis[x] + :: x[i]) {
                dis[y] = dis[x] + :: x[i];
                if(!inq[y]) {
                    inq[y] = 1;
                    q.push(y);
                }
            }
        }
    }
}

int main() {
    scanf("%lld%lld%lld%lld", &h, &a, &b, &c);
    h --;
    x[0] = a, x[1] = b, x[2] = c;
    sort(x, x + 3, greater<ll> ());
    mn = x[2];
    spfa();
    ll ans = 0;
    for(ll i = 0 ; i < mn ; ++ i) {
       if(dis[i] <= h) ans += (h - dis[i]) / mn + 1;
    }
    printf("%lld\n", ans);
}
