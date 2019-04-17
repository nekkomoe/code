#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 310, mod = 1e9 + 7;

int n, m;
vector<pair<int, int> > g[N];
ll f[N][N][N], ans;

void upd(ll &x, ll y) {
    x = (x + y) % mod;
    if(x < 0) x += mod;
}

int check(int x, int y, int z) {
    if(x && y && x == y) return 0;
    if(x && z && x == z) return 0;
    if(y && z && y == z) return 0;
    int mx = max(max(x, y), z);
    for(auto t: g[mx]) {
        int l = t.first, tmp = 0;
        tmp += x >= l;
        tmp += y >= l;
        tmp += z >= l;
        if(tmp != t.second) return 0;
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int l, r, x; scanf("%d%d%d", &l, &r, &x);
        g[r].push_back(make_pair(l, x));
    }
    f[0][0][0] = 1;
    for(int i = 0 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= n ; ++ j) {
            for(int k = 0 ; k <= n ; ++ k) {
                if(!check(i, j, k)) continue;
                ll s = f[i][j][k];
                ll mx = max(max(i, j), k);
                ll sum = f[i][j][k];
                upd(f[mx + 1][j][k], sum);
                upd(f[i][mx + 1][k], sum);
                upd(f[i][j][mx + 1], sum);
                if(mx == n) {
                    upd(ans, sum);
                }
            }
        }
    }
    printf("%lld\n", ans);
}
