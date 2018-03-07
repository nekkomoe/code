#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int n, m, v[N], phi[N], prime[N], pTot;

ll f[N];

void build() {
    f[1] = phi[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!v[i]) prime[++ pTot] = (phi[i] = i - 1) + 1;
        for(int j = 1 ; j <= pTot && i * prime[j] <= n ; ++ j) {
            v[i * prime[j]] = 1;
            if(i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
        f[i] = f[i - 1] + phi[i];
    }
}

ll sol() {
    ll ans = 0;
    for(int i = 1, j ; i <= min(n, m) ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (f[j] - f[i - 1]) * (n / i) * (m / j);
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    build();
    printf("%lld\n", 2 * sol() - (ll) n * m);
}
