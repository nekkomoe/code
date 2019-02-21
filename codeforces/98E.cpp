#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1010;
ld F[N][N]; int vis[N][N];

ld f(int n, int m) {
    if(!n) return (ld) 1 / (m + 1);
    if(!m) return 1;
    if(vis[n][m]) return F[n][m];
    ld k1 = (ld) m / (m + 1) * (1 - f(m - 1, n)) - 1;
    ld b1 = 1;
    ld k2 = (ld) (1 + m * (1 - f(m - 1, n))) / (m + 1) - (1 - f(m, n - 1));
    ld b2 = 1 - f(m, n - 1);
    ld X = (b2 - b1)  / (k1 - k2);
    vis[n][m] = 1;
    return F[n][m] = k1 * X + b1;
}

int main() {
    int n, m; cin >> n >> m;
    ld ans = f(n, m);
    cout << fixed << setprecision(10) << ans << ' ' << (1 - ans) << endl;
}
