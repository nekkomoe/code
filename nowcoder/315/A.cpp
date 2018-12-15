#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n; cin >> n; ll x = 0;
    for(ll i = 1 ; i * i <= n ; ++ i)
        x = i;
    cout << x * x << endl;
}

