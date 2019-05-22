#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll C(ll n, ll m) {
    if(n < m || m < 0) {
        return 0;
    }
    if(m == 2) {
        return n * (n - 1) / 2;
    } else {
        // return (n!) / (6) / (n - 3)!;
        return n * (n - 1) * (n - 2) / 6;
    }
}

int main() {
    ll x;
    while(cin >> x) {
        cout << (x+(x-1)*(x-2)*(x*x-3*x+12)/24) << endl;
    }
}
