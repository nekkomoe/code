#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

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

int calc(int a, int b, int c, int d) {
    const int lim = 1100;
    bitset<lim + 1> vis;
    vis = 0;
    for(int i = 0 ; a * i <= lim ; ++ i) {
        for(int j = 0 ; a * i + b * j <= lim ; ++ j) {
            for(int k = 0 ; a * i + b * j + c * k <= lim ; ++ k) {
                for(int l = 0 ; a * i + b * j + c * k + l * d <= lim ; ++ l) {
                    vis[a * i + b * j + c * k + l * d] = 1;
                }
            }
        }
    }

    int res = 0;
    for(int i = lim ; i ; -- i) {
        if(vis[i] == 0) {
            ++ res;
        }
    }
    return res;
}

int calc(int a, int b, int c) {
    const int lim = 110;
    bitset<lim + 1> vis;
    vis = 0;
    for(int i = 0 ; a * i <= lim ; ++ i) {
        for(int j = 0 ; a * i + b * j <= lim ; ++ j) {
            for(int k = 0 ; a * i + b * j + c * k <= lim ; ++ k) {
                vis[a * i + b * j + c * k] = 1;
            }
        }
    }

    int res = 0;
    for(int i = lim ; i ; -- i) {
        if(vis[i] == 0) {
            ++ res;
        }
    }
    return res;
}

int calc(int a, int b) {
    const int lim = 11000;
    bitset<lim + 1> vis;
    vis = 0;
    for(int i = 0 ; a * i <= lim ; ++ i) {
        for(int j = 0 ; a * i + b * j <= lim ; ++ j) {
            vis[a * i + b * j] = 1;
        }
    }
    int res = 0;
    for(int i = lim ; i ; -- i) {
        if(vis[i] == 0) {
            // return i;
            ++ res;
        }
    }
    // return -1;
    return res;
}

ll mul(ll a, ll b) {
    return (a % mod) * (b % mod) % mod;
}

ll f(ll n) {
    return n < 0 ? 0 : mul(mul(n, n + 1), (mod + 1) / 2);
}

int main() {
    int t; scanf("%d", &t);
    ll n, k, ans;
    while(t --) {
        scanf("%lld%lld", &n, &k);
        k = k + n - 3;
        -- n;
        ans = 0;
        ans = (mul(n, f(k / n - 1)) + mul(k / n, k - k / n * n + 1)) % mod;
        printf("%lld\n", ans);
    }
}
