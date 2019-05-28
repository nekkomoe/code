#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int isp(ll x) {
    for(ll i = 2 ; i * i <= x ; ++ i) {
        if(x % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    ll n; cin >> n;
    if(n <= 3 || isp(n)) {
        puts("1");
    } else if(n % 2 == 0) {
        puts("2");
    } else if(isp(n - 2)) {
        puts("2");
    } else {
        puts("3");
    }
}
