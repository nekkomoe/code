#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int mod = 23333;

namespace NEKKO {

    int NEKODEBG = 0;

    void runprog() {

        function<ll(ll)> query = [&] (ll x) {

            if(NEKODEBG) {
                return x * x % mod;
            }

            ll res;
            printf("1 %lld\n", x);
            fflush(stdout);
            scanf("%lld", &res);
            return res; // 在返回了
        };

        function<ll(ll, ll)> gcd = [&] (ll a, ll b) {
            return b ? gcd(b, a % b) : a;
        };

        function<vector<ll>(ll)> split = [&] (ll n) {
            vector<ll> res;
            for(ll i = 2 ; i * i <= n ; ++ i) {
                if(n % i == 0) {
                    res.emplace_back(i);
                    while(n % i == 0) {
                        n /= i;
                    }
                }
            }
            if(n > 1) {
                res.emplace_back(n);
            }
            return res;
        };

        ll bird_num[2] = {
            3 * 5 * 5 * 317,
            3 * 1145141
        };

        ll res_num[2] = {
            query(bird_num[0]),
            query(bird_num[1])
        };


        ll del_num[2] = {
            bird_num[0] * bird_num[0] - res_num[0],
            bird_num[1] * bird_num[1] - res_num[1]
        };

        ll g = gcd(del_num[0], del_num[1]);
        auto sig = split(g);

        ll ans = 0;
        for(auto p: sig) {
            if(bird_num[0] * bird_num[0] % p == res_num[0]) {
                if(bird_num[1] * bird_num[1] % p == res_num[1]) {
                    ans = p;
                    break;
                }
            }
        }
        
        printf("2 %lld\n", ans);
        fflush(stdout);

        if(NEKODEBG) {
            assert(ans == mod);
        }

        if(!NEKODEBG) {
            scanf("%*s"); // 在读结果了
        }
    }

    void main() {
        int t; scanf("%d", &t);
        while(t --) {
        // int start = 1;
        // while(1) {
        //     if(NEKODEBG) {
        //         // int start = rand() % int(2) + 2;
        //         while(1) {
        //             mod = ++ start;
        //             // mod = rand() % int(1e9) + 2;
        //             for(ll i = 2 ; i * i <= mod ; ++ i) {
        //                 if(mod % i == 0) {
        //                     mod = -1;
        //                     break;
        //                 }
        //             }
        //             if(mod != -1) {
        //                 break;
        //             }
        //         }
        //         printf("mod = %d\n", mod);
        //     }

            runprog();
        }
    }
}

int main() {
    NEKKO :: main();
}

/*
    mod = 17
    mod = 23333
*/
