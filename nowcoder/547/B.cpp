#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    int t; cin >> t;
    while(t --) {
        int x, y, v, ans = 0;
        cin >> x >> y;
        v = y;
        while(v * 100 < 299792458) {
            ++ ans;
            v = 2 * x + y;
            x = v;    
        }
        printf("%d\n", ans);
    }
}
