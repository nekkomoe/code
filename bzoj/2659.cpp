#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll f(ll a, ll b, ll c, ll n) {
    if(n <= 0) return 0;
    return n * (n - 1) / 2 * (a / c) + n * (b / c) + f(c, (a * n + b) % c, a % c, (a % c * n + b % c) / c);
}
 
int main() {
    ll p, q; cin >> p >> q;
    cout << f(q, 0, p, (p - 1) / 2 + 1) + f(p, 0, q, (q - 1) / 2 + 1) << endl;
}
?
