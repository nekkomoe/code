#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

int main() {
    ll n; cin >> n;
    if(n & 1) cout << 1 << endl;
    else cout << (n / 2) % mod * ((n / 2 + 1) % mod) % mod << endl;
}
