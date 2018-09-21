#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int main() {
    ll n; cin >> n;
    if(n & 1) {
        ll a = n, b = n;
        a -= b / 2;
//      cout << a << ' ' << b << endl;
        b -= a;
//      cout << a << ' ' << b << endl;
        a = max(a - b, 0ll);
//      cout << a << ' ' << b << endl;
        cout << (a + b) << endl;
    }
    else cout << n / 2 << endl;
}
