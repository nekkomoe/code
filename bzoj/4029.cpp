#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll f(ll n) {
    ll res = 1;
    while(n % 10 == 0) n /= 10, res *= 10;
    return res;
}

ll calc(ll n) {
    while(n % 10 == 0) n /= 10;
    ll res = n % 10, len = 0;
    while(n) ++ len, n /= 10;
    return 2 * len - (res == 5);
}

void sol() {
    ll L, R, mn, ans;
    cin >> L >> R; mn = calc(ans = L);
    while(L <= R) {
        L += f(L);
        if(L <= R) {
            ll t = calc(L);
            if(t < mn) {
                mn = t, ans = L;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios :: sync_with_stdio(0);
    int T; cin >> T;
    while(T --) sol();
} 

