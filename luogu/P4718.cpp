// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    // ---------------------------------------DECLARE--------------------------------------
    const int mod = 1e9 + 7;

    auto pw = [&] (ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod) {
            if(b & 1) {
                r = r * a % mod;
            }
        }
        return r;
    };

    auto getinv = [&] (ll n) {
        return pw(n, mod - 2);
    };

    auto upd = [&] (ll &a, ll b) {
        a = (a + b) % mod;
    };

    auto get_fac_invfac = [&] (int n) {
        vector<int> fac(n + 5), invfac(n + 5);
        fac[0] = invfac[0] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            fac[i] = (ll) fac[i - 1] * i % mod;
        }
        invfac[n] = getinv(fac[n]);
        for(int i = n - 1 ; i >= 1 ; -- i) {
            invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
        }
        return make_pair(fac, invfac);
    };

    auto C = [&] (int n, int m) {
        const int MXN = 1e5;
        static vector<int> fac, invfac;
        static int flag = ([&] () {
            auto tmp = get_fac_invfac(MXN + 5);
            fac = tmp.first, invfac = tmp.second;
            return 0;
        }) ();
        return n < m || m < 0 ? 0 : (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    };

    // ----------------------------------------BEGIN---------------------------------------

    int t; scanf("%d", &t);
    while(t --) {
        ll n; scanf("%lld", &n);
        auto mul = [&] (ll a, ll b, ll mod) {
            return ((ll) (a * b - (ll) ((long double) a * b / mod) * mod) % mod + mod) % mod;
        };
        auto pw = [&] (ll a, ll b, ll mod) {
            ll r = 1;
            for( ; b ; b >>= 1, a = mul(a, a, mod)) {
                if(b & 1) {
                    r = mul(r, a, mod);
                }
            }
            return r;
        };
        auto checkpri = [&] (ll n) {
            if(n <= 1) {
                // puts("不理解");
                // assert(0);
                return 0;
            }
            const auto pri = { 2, 3, 5, 7, 11, 23, 47 };
            for(ll x: pri) {
                if(n == x) {
                    return 1;
                }
            }
            for(ll p: pri) {
                ll coef = n - 1, tot = 0;
                while((coef & 1) == 0) {
                    coef >>= 1;
                    ++ tot;
                }
                ll pro = pw(p, coef, n);
                if(pro == 1) {
                    continue;
                }
                bool flag = pro == n - 1;
                while(tot) {
                    -- tot;
                    pro = mul(pro, pro, n);
                    flag |= pro == n - 1;
                    if(pro == 1 && flag == 0) {
                        return 0;
                    }
                }
                if(pro != 1 || flag == 0) {
                    return 0;
                }
            }
            return 1;
        };
        if(checkpri(n)) {
            puts("Prime");
            continue;
        }
        ll res = 0;
        auto pollardrho = [&] (ll n) {
            if(n % 2 == 0) {
                return 2ll;
            }
            ll c = rand() % (n - 2) + 1;
            auto f = [&] (ll x) {
                return (mul(x, x, n) + c) % n;
            };
            function<ll(ll, ll)> gcd = [&] (ll a, ll b) {
                if(!a || !b) return a | b;
                #define ctz __builtin_ctzll
                int shift = ctz(a|b);
                b >>= shift;
                while(a) {
                    a >>= ctz(a);
                    a < b ? swap(a,b) : void();
                    a -= b;
                }
                return b << shift;
                #undef ctz
            };
            ll x = 0, y = 0, d = 1;
            for(ll i = 2, pro = 1 ; ; i <<= 1, y = x, pro = 1) {
                for(ll j = 1 ; j <= i ; ++ j) {
                    x = f(x);
                    pro = mul(pro, abs(x - y), n);
                    if((j & 127) == 0) {
                        d = gcd(pro, n);
                        if(d > 1) {
                            break;
                        }
                    }
                }
                if(d > 1 || (d = gcd(pro, n)) > 1) {
                    break;
                }
            }
            if(d == n) {
                d = 1;
                while(d == 1) {
                    x = f(x);
                    d = gcd(abs(x - y), n);
                }
            }
            return d;
        };
        function<void(ll)> sol = [&] (ll n) {
            if(checkpri(n)) {
                res = max(res, n);
            } else {
                ll sig = n;
                while(sig == n) {
                    sig = pollardrho(n);
                }
                sol(n / sig), sol(sig);
            }
        };
        sol(n);
        printf("%lld\n", res);
    }

    // -----------------------------------------END----------------------------------------

    return 0;
}
