#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    int n; ll ans = 0;
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        ll x, y; cin >> x >> y;
        ans += y - x;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        ll x, y; cin >> x >> y;
        ans += x - y;
    }
    cout << ans << endl;
}
