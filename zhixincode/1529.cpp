#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld;

ld l, r, L, R;

int main() {
    cin >> l >> r >> L >> R;
    ld a = (L + R) / 2;

    ld x = (a + l) / 2;
    if(x > r) x = r;
    else if(x < l) x = l;

    cout << fixed << setprecision(4) << max((-x * x + (a + l) * x - l * a) / (r - l), (ld) 0) << endl;
}
