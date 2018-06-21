#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
ll n, p, m, ans, r, s2[N], s4[N], s6[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
    return r;
}

int main() {
    cin >> n; p = 1e9 + 7;
    m = n % p, r = sqrt(n);
    for(ll i = 1 ; i <= r ; ++ i) {
        s2[i] = (s2[i - 1] + pw(i, 2)) % p;
        s4[i] = (s4[i - 1] + pw(i, 4)) % p;
        s6[i] = (s6[i - 1] + pw(i, 6)) % p;
    }
    for(ll x = -r ; x <= r ; ++ x) {
        ll y = sqrt(n - x * x);
        ll x2 = pw(x, 2);
        ll x4 = pw(x, 4);
        ll x6 = pw(x, 6);
        ll res = 0;
        res += 2 * x6 % p * y % p;                                                      res %= p;
        res += 6 * x4 % p * s2[y] % p;                                                  res %= p;
        res += 6 * x2 % p * s4[y] % p;                                                  res %= p;
        res += 2 * s6[y] % p;                                                           res %= p;
        res -= 3 * (m + 2) % p * (x4 * y % p + 2 * x2 % p * s2[y] % p + s4[y] % p) % p; res %= p;
        res += (3 * m % p + 4) % p * (x2 * y % p + s2[y] % p) % p;                      res %= p;
        res *= 2;                                                                       res %= p;
        res += (pw(m, 3) + 3 * pw(m, 2) % p + 2 * m % p) % p * (2 * y % p + 1) % p;     res %= p;
        res += 2 * x6 % p - 3 * (m + 2) % p * x4 % p + (3 * m % p + 4) * x2 % p;        res %= p;
        ans = (ans + res) % p;
    }
    ans = (ans % p + p) % p;
    cout << ans * pw(6, p - 2) % p << endl;
}
