#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;
typedef long long ll;
int n, k, x;
ll pre[N], sub[N], a[N];
int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> k >> x;
    for(int i = 1 ; i <= n ; ++ i) cin >> a[i], pre[i] = sub[i] = a[i], pre[i] = pre[i - 1] | pre[i];
    for(int i = n ; i ; -- i) sub[i] = sub[i + 1] | sub[i];
    ll ans = 0, tmp = 1;
    for(int i = 1 ; i <= k ; ++ i) tmp *= x;
    for(int i = 1 ; i <= n ; ++ i) ans = max(ans, pre[i - 1] | sub[i + 1] | a[i] * tmp);
    cout << ans << endl;
}
