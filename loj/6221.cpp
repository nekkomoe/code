#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    scanf("%lld", &n);
    vector<ll> two, three;
    for(ll i = 1 ; i * i <= n ; ++ i) {
        two.emplace_back(i * i);
    }
    for(ll i = 1 ; i * i * i <= n ; ++ i) {
        three.emplace_back(i * i * i);
    }
    set<ll> s;
    for(auto a: two) {
        for(auto b: three) {
            if(a * b <= n) {
                s.emplace(a * b);
            } else {
                break;
            }
        }
    }
    ll sum = 0; for(auto x: s) sum += x;
    printf("%lld\n%lld\n", (ll) s.size(), sum);
}
