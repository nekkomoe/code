#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;

typedef long long ll;

ll p[N], s[N], f[2][N], pre, c;

int main() {
    cin >> n >> c;
    for(int i = 1 ; i <= n ; ++ i) cin >> p[i];
    for(int i = 1 ; i <= n ; ++ i) cin >> s[i];
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        pre ^= 1;
        for(int j = 0 ; j <= i ; ++ j) {
            f[pre][j] = f[pre ^ 1][j] + p[i] + c * j;
            if(j) f[pre][j] = min(f[pre][j], f[pre ^ 1][j - 1] + s[i]);
        }
    }
    ll ans = f[pre][0];
    for(int i = 1 ; i <= n ; ++ i) ans = min(ans, f[pre][i]);
    cout << ans << endl;
}
