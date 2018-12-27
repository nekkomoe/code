#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    long double a, b, c, d, l, r, ans = 0;
    cin >> a >> b >> c >> d >> l >> r;
    if(fabs(a) < 1e-6) {
        ans += (c * r * r / 2 + d * r - c * l * l / 2 - d * l) / b;
    } else {
        ans += (r - l) * c / a;
        ans += (d - b * c / a) / a * (log(abs(a * r + b)) - log(abs(a * l + b)));
    }
    cout << fixed << setprecision(6) << ans << endl;
}

