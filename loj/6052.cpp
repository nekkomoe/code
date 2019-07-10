#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace NEKKO {

    const int mod = 1004535809, N = 1e5 + 10, inv2 = (mod + 1) / 2;

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

    void upd(ll &a, ll b) {
        a = (a + b) % mod;
    }

    void main() {
        ll n; cin >> n;

        auto D = [&] (ll n) {

            static vector<ll> D_small = ([&] () {
                const int n = 1e7;
                vector<ll> res(n + 5), vis(n + 5), pri;
                res[1] = 1;
                for(int i = 2 ; i <= n ; ++ i) {
                    if(!vis[i]) {
                        pri.emplace_back(i);
                        res[i] = 1 + i;
                    }
                    for(auto p: pri) {
                        if(i * p > n) {
                            break;
                        }
                        vis[i * p] = 1;
                        res[i * p] = res[i] * res[p] % mod;
                        if(i % p == 0) {
                            (res[i * p] -= p * res[i / p] % mod) %= mod;
                            break;
                        }
                    }
                }
                for(int i = 2 ; i <= n ; ++ i) {
                    (res[i] += res[i - 1]) %= mod;
                }
                return res;
            })();

            if(n <= int(1e7)) {
                return D_small[n];
            }

            static unordered_map<ll, ll> mem;
            if(mem.count(n)) {
                return mem[n];
            }

            ll res = 0;
            for(ll i = 1, j ; i <= n ; i = j + 1) {
                j = n / (n / i);
                ll val = (i % mod + j % mod) * (j % mod - i % mod + 1) % mod * inv2 % mod;
                upd(res, (n / i) % mod * val % mod);
            }
            return mem[n] = res;
        };

        auto G = [&] (ll k) {
            static unordered_map<ll, ll> mem;
            if(mem.count(k)) {
                return mem[k];
            }
            ll res = 0;
            for(ll p = 1 ; p * p <= k ; ++ p) {
                upd(res, p % mod * (ll) (sqrt(k - p * p)) % mod);
            }
            return mem[k] = res;
        };

        function<ll(ll)> F = [&] (ll k) -> ll {
            if(k <= 1) {
                return 0;
            }

            static vector<ll> F_small = ([&] () {
                int n = 1e5;
                function<ll(ll, ll)> gcd = [&] (ll a, ll b) -> ll {
                    return b ? gcd(b, a % b) : a;
                };
                vector<ll> res(n + 5);
                for(ll i = 1 ; i * i <= n ; ++ i) {
                    ll sqr = i * i;
                    for(ll j = 1 ; j * j + sqr <= n ; ++ j) {
                        if(gcd(i, j) == 1) {
                            (res[j * j + sqr] += i) %= mod;
                        }
                    }
                }
                for(ll i = 1 ; i <= n ; ++ i) {
                    (res[i] += res[i - 1]) %= mod;
                }
                return res;
            })();

            if(k <= int(1e5)) {
                return F_small[k];
            }

            static unordered_map<ll, ll> mem;
            if(mem.count(k)) {
                return mem[k];
            }

            ll res = G(k);
            for(ll d = 2 ; d * d <= k ; ++ d) {
                upd(res, -d % mod * F(k / d / d) % mod);
            }
            return mem[k] = res;
        };


        auto sol = [&] (ll n) {
            ll res = 0;
            for(ll i = 1, j ; i <= n ; i = j + 1) {
                j = n / (n / i);
                upd(res, (F(j) - F(i - 1)) % mod * D(n / i) % mod);
            }
            return res;
        };

        ll ans = (sol(n) * 2 % mod + D(n)) % mod;
        cout << (ans % mod + mod) % mod << endl;
    }
}

int main() {
    NEKKO :: main();    
}
