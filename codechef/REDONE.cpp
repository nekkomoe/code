#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e6 + 10;

ll fac[N];
void init(int n) {
    fac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
}

void runprog() {
    ll n; scanf("%lld", &n);
    printf("%lld\n", fac[n + 1] - 1);
}

int main() {
    init(N - 1);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
