#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace NEKKO {

    int NEKKODEBUG = 0;

    void runprog() {
        int q; scanf("%d", &q);

        auto cnt = array<ll, int(1e6)> ();
        for(int i = 0 ; i < int(5e5) ; ++ i) {
            cnt[i] = cnt[i >> 1] + (i & 1);
        }

        auto a = array<ll, 110> ();
        auto st = set<int> ();

        ll even = 0, odd = 0;

        while(q --) {
            ll x, tx; scanf("%lld", &x), tx = x;
            for(ll i = 30 ; ~ i ; -- i) {
                if((x >> i) & 1) {
                    if(!a[i]) {
                        a[i] = x;
                        break;
                    } else {
                        x ^= a[i];
                    }
                }
            }
            if(x) {
                // puts("INSERT");
                x = tx;
                set<int> ns(st);
                ns.emplace(x);
                for(auto y: st) {
                    int z = x ^ y;
                    if(z) {
                        ns.emplace(z);
                    }
                }
                st = ns;
                odd = even = 0;
                for(auto t: st) {
                    if(cnt[t] & 1) {
                        ++ odd;
                    } else {
                        ++ even;
                    }
                }
            }
            printf("%lld %lld\n", even, odd);
        }
    }

    void main() {
        int t; scanf("%d", &t);
        while(t --) {
            runprog();
        }
    }
}

int main() {
    NEKKO :: main();
}
