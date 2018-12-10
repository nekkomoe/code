#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

ll n, k, a[N], ans;

ll f1(ll n) {
    return n <= 4 ? int("01012"[n] - '0') : n & 1 ? 0 : f1(n / 2) == 1 ? 2 : 1;
}

ll f2(ll n) {
    return n <= 2 ? n : 1 - n % 2;
}

int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i];
        ans ^= k & 1 ? f1(a[i]) : f2(a[i]);
    }
    cout << (ans ? "Kevin" : "Nicky") << endl;
}

