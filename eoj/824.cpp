#include "bits/stdc++.h"
using namespace std;
typedef unsigned long long ull;
const int N = 1e6 + 10;
const double eps = (1 + sqrt(5)) / 2;

ull pri[N], tot, mu[N], vis[N];
const int T = 2e7 + 10;
ull to[T];
unsigned head[T], rest[T];
inline void add(unsigned u, ull v) {
    static unsigned tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

inline ull S(ull n, ull p) {
    ull res = 0;
    for(unsigned i = head[p] ; i ; i = rest[i]) {
        ull d = to[i];
        res += (p / d - n / d) * mu[d];
    }
    return res;
}

inline ull sol(ull n) {
    ull ans = 0;
    for(ull p = 1, limp = sqrt(n) ; p <= limp ; ++ p) {
        ans += S(floor(p / eps), p) * (n / p / p);
    }
    return ans;
}

inline void init(ull n) {
    mu[1] = 1;
    for(ull i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(ull j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                break;
            } else {
                mu[i * pri[j]] = -mu[i];
            }
        }
    }
    for(ull i = 1 ; i <= n ; ++ i) {
        for(ull j = i ; j <= n ; j += i) {
            add(j, i);
        }
    }
}

signed main() {
    ull n; cin >> n;
    init(sqrt(n));
    cout << sol(n) << endl;
}
