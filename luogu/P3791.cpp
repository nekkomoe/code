// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 1e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

ll n, m, x, ans;
unordered_map<ll, ll> mem;
ll calc(ll n) {
    if(n <= 0) return 0;
    if(mem.count(n)) return mem[n];
    ll res = 0;
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = (res + (j - i + 1) % mod * ((n / i) % mod) % mod) % mod;
    }
    return mem[n] = res;
}

int main() {
    cin >> n >> m >> x;
    ++ n, ++ m; // lcp < len
    for(ll i = 35 ; ~ i ; -- i) {
        if((n >> i) & 1) {
            for(ll j = 35 ; ~ j ; -- j) {
                if((m >> j) & 1) {
                    ll mn = min(i, j), mx = max(i, j);
                    ll sum = x ^ (x & ((1ll << mx) - 1));
                    ll N = n ^ (1ll << i), M = m ^ (1ll << j);
                    sum ^= N ^ (N & ((1ll << mx) - 1));
                    sum ^= M ^ (M & ((1ll << mx)) - 1);
                    ll res = (calc(sum ^ ((1ll << mx) - 1)) - calc(sum - 1)) % mod;
                    res = res * pw(2, mn) % mod;
                    ans = (ans + res) % mod;
                }
            }
        }
    }
    cout << (ans % mod + mod) % mod << endl;
}
