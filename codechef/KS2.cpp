#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void runprog() {
    ll n; scanf("%lld", &n);
    cout << n;
    ll x = 0;
    while(n) {
        x += n % 10;
        x %= 10;
        n /= 10;
    }
    cout << (x == 0 ? 0 : 10 - x) << endl;
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
