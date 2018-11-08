#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int n, m, sum, ans;
struct T {
    int cost;
    ld a[510];
} t[510]; bool operator < (T a, T b) { return a.cost < b.cost; }
int vis[510]; ld a[510];

int main() {
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j)
            cin >> t[i].a[j];
    for(int i = 1 ; i <= n ; ++ i)
        cin >> t[i].cost;
    sort(t + 1, t + 1 + n);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j)
            if(fabs(t[i].a[j]) > 1e-7) {
                if(!vis[j]) {
                    vis[j] = i, sum ++, ans += t[i].cost;
                    break;
                } else {
                    ld x = t[i].a[j] / t[vis[j]].a[j];
                    for(int k = j ; k <= m ; ++ k) {
                        t[i].a[k] -= x * t[vis[j]].a[k];
                    }
                }
            }
    cout << sum << ' ' << ans << endl;
}
