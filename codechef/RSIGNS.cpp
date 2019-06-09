#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
int k;

void runprog() {
    scanf("%d", &k);
    printf("%lld\n", 10 * pw(2, k - 1) % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
