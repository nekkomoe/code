#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int N = 5000010;
 
ll n, sa, sb, sc, sd, a[N], mod, ans, mx = 0xcfcfcfcfcfcfcfcfll;
 
ll f(ll x) {
    return ((((sa % mod * x % mod * x % mod * x % mod
        + sb % mod * x % mod * x % mod) % mod
        + sc % mod * x % mod) % mod) % mod
        + sd % mod) % mod;
}
 
int main() {
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> sa >> sb >> sc >> sd >> a[1] >> mod;
    for(int i = 1 ; i <= n ; ++ i) {
        if(i > 1) a[i] = (f(a[i - 1]) + f(a[i - 2])) % mod;
        if(mx <= a[i]) mx = a[i];
        else ans = max(ans, (mx - a[i] + 1) >> 1);
    }
    cout << ans << endl;
}
