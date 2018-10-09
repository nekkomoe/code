// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e6 + 10;
struct A { int pos, val; } a[N];
bool operator < (A a, A b) { return a.pos < b.pos; }
int n, m, b[N]; ll f[N][2];

int main() {
// 	freopen("data.in", "r", stdin);
    scanf("%*d%d", &m);
    for(int i = 1 ; i <= m ; ++ i) scanf("%d%d", &a[i].pos, &a[i].val);
    sort(a + 1, a + 1 + m);
    for(int i = 1, lst = 0 ; i <= m ; ++ i) {
        if(a[i].pos - 1 - lst >= 1) b[++ n] = -1;
        if(a[i].pos - 1 - lst >= 2) b[++ n] = -1;
        b[++ n] = a[i].val;
        lst = a[i].pos;
    }
    ll ans = 0; f[0][1] = 1e15;
    for(int i = 30 ; ~ i ; -- i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(b[j] >= 0) {
                if((b[j] >> i) & 1) {
                    f[j][0] = f[j - 1][1];
                    f[j][1] = f[j - 1][0] + (1ll << i);
                } else {
                    f[j][0] = f[j - 1][0];
                    f[j][1] = f[j - 1][1] + (1ll << i);
                }
            } else {
                f[j][0] = min(f[j - 1][0], f[j - 1][1]);
                f[j][1] = min(f[j - 1][0] + (1ll << i), f[j - 1][1] + (1ll << i));
            }
        }
        ans += min(f[n][0], f[n][1]);
    }
    printf("%lld\n", ans);
}