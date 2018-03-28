//二分

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long ll;

int n;

ll Sa, Sb, Sc, Sd, A[5000010], Mod, ans;

inline ll F(ll x) {
    ll t0 = x % Mod;
    ll t1 = ((t0 * t0) % Mod) % Mod;
    ll t2 = (t1 * t0) % Mod;
    return (((Sa * t2) % Mod) +
            ((Sb * t1) % Mod) +
            ((Sc * t0) % Mod) +
            Sd) % Mod;
}

bool check(ll x) {
    ll mx = 1;
    for(int i = 1 ; i <= n ; i ++) {
        mx = max(mx, A[i] - x);
        if(mx > A[i] + x) return 0;
    }
    return 1;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> Sa >> Sb >> Sc >> Sd >> A[1] >> Mod;
    for(int i = 2 ; i <= n ; i ++) {
        A[i] = F(A[i - 1]) + F(A[i - 2]);
        A[i] %= Mod;
    }
    ll L = 0, R = Mod;
    while(L <= R) {
        ll M = (L + R) / 2;
        if(check(M)) {
            ans = M;
            R = M - 1;
        } else {
            L = M + 1;
        }
    }
    cout << ans << endl;
}
