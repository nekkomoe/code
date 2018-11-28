#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ll ans = 0, n;
    cin >> n;
    for(ll i = 2 ; i <= n ; ++ i)
        for(ll j = 2 ; i * j <= n ; ++ j)
            ans += j;
    cout << ans * 4 << endl;
}

