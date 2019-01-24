#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

namespace getg {
    int sig[int(1e7)];
    ll pw(ll a, ll b, ll mod) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod)
            if(b & 1)
                r = r * a % mod;
        return r;
    }
    int get(int p) {
        int x = p - 1, tot = 0;
        for(int i = 2 ; 1ll * i * i <= x ; ++ i) {
            if(x % i) continue;
            sig[++ tot] = i;
            if(x / i > i) sig[++ tot] = x / i;
        }
        for(int g = 2 ; ; ++ g) {
            bool flag = 1;
            for(int i = 1 ; i <= tot ; ++ i) {
                if(pw(g, sig[i], p) == 1) {
                    flag = 0;
                    break;
                }
            }
            if(flag) return g;
        }
        assert(0);
        return -1;
    }
}

int main() {
    int p; scanf("%d", &p);
    printf("%d\n", getg :: get(p));
}

