#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int n, q, a[N], vis[N], cnt[N], sz;
vector<int> o[N];
vector<int> split(int n) {
    vector<int> res;
    for(int i = 2 ; i * i <= n ; ++ i) {
        if(n % i) continue;
        res.push_back(i);
        while(n % i == 0) n /= i;
    }
    if(n > 1) res.push_back(n);
    return res;
}
ll calc(int x, int t) {
    ll ans = 0;
    for(int s = 0 ; s < (1 << o[x].size()) ; ++ s) {
        int pro = 1, tot = 0;
        for(int i = 0 ; i < o[x].size() ; ++ i) {
            if((s >> i) & 1) {
                ++ tot;
                pro *= o[x][i];
            }
        }
        if(t == -1) -- cnt[pro];
        ans += (tot & 1 ? -1 : 1) * cnt[pro];
        if(t == 1) ++ cnt[pro];
    }
    return ans;
}
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        o[i] = split(a[i]);
    }
    ll ans = 0;
    for(int i = 1, x ; i <= q ; ++ i) {
        scanf("%d", &x);
        if(vis[x]) {
            ans -= calc(x, -1);
        } else {
            ans += calc(x, 1);
        }
        vis[x] ^= 1;
        printf("%lld\n", ans);
    }
}
