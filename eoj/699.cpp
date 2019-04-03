#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll l, r, k, res;

int main() {
    cin >> l >> r >> k;
    res = r - l + 1;
    if(k >= 2) {
        for(ll x = 1, y ; x < l ; x = y + 1) {
            y = min((l - 1) / ((l - 1) / x), r / (r / x));
            if(r / x - (l - 1) / x >= 2) {
                res += y - x + 1;
            }
        }
    }
    cout << res << endl;
}
