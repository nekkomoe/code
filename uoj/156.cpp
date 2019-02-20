#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const long double eps = 1e-7;
long double u0, u1, a, b, c;
ll n;

int main() {
    cin >> u0 >> u1 >> a >> b >> c >> n;
    if(n == 0) cout << fixed << setprecision(10) << u0;
    else {
        long double x;
        while(n --) {
            x = a + b / u1 + c / (u0 * u1); int flag = 0;
            if(fabs(x - u1) < eps && fabs(u1 - u0) < eps) {
                flag = 1;
            }
            u0 = u1, u1 = x;
            if(flag) break;
        }
        cout << fixed << setprecision(10) << u0;
    }
}
