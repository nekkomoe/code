#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void sol() {
    ll a, b; scanf("%lld%lld", &a, &b);
    if(gcd(a, b) == 1) {
        printf("1\n%lld %lld\n", a, b);
    } else {
        for(ll i = 2 ; i <= 10 ; ++ i) {
            ll a1 = i, a2 = a - i;
            if(a2 >= 2) {
                for(ll j = 2 ; j <= 10 ; ++ j) {
                    ll b1 = j, b2 = b - j;
                    if(b2 >= 2) {
                        if(gcd(a1, b1) == 1 && gcd(a2, b2) == 1) {
                            printf("2\n%lld %lld\n%lld %lld\n", a1, b1, a2, b2);
                            return ;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        sol();
    }
}
