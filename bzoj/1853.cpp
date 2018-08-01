#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll seq[N], a[N], ans, l, r;
int tot, cnt;
bool vis[N];
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline void init(ll cur) {
    if(cur > (ll) 1e10) return ;
    seq[++ tot] = cur;
    init(cur * 10 + 6);
    init(cur * 10 + 8);
}
inline void dfs(int step, int size, ll val) {
    if(val > r) return ;
    if(step > cnt) {
        if(size) {
            ans += (size % 2 ? 1 : -1) * (r / val - (l / val + (l % val != 0)) + 1);
        }
        return ;
    }
    dfs(step + 1, size, val);
    ll t = val / gcd(val, a[step]);
    if((double) t * a[step] <= r) {
        dfs(step + 1, size + 1, t * a[step]);
    }
}
int main() {
    scanf("%lld%lld", &l, &r);
    init(6), init(8);
    sort(seq + 1, seq + 1 + tot);
    for(int i = 1 ; i <= tot ; ++ i) {
        if(!vis[i]) a[++ cnt] = seq[i];
        for(int j = i + 1 ; j <= tot ; ++ j) {
            if(seq[j] % seq[i] == 0) {
                vis[j] = 1;
            }
        }
    }
    sort(a + 1, a + 1 + cnt, greater<ll> ());
    dfs(1, 0, 1);
    printf("%lld\n", ans);
}
